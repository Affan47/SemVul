target_do_xcopy(struct se_cmd *se_cmd)
{
	struct se_device *dev = se_cmd->se_dev;
	struct xcopy_op *xop = NULL;
	unsigned char *p = NULL, *seg_desc;
	unsigned int list_id, list_id_usage, sdll, inline_dl, sa;
	sense_reason_t ret = TCM_INVALID_PARAMETER_LIST;
	int rc;
	unsigned short tdll;

	if (!dev->dev_attrib.emulate_3pc) {
		pr_err("EXTENDED_COPY operation explicitly disabled\n");
		return TCM_UNSUPPORTED_SCSI_OPCODE;
	}

	sa = se_cmd->t_task_cdb[1] & 0x1f;
	if (sa != 0x00) {
		pr_err("EXTENDED_COPY(LID4) not supported\n");
		return TCM_UNSUPPORTED_SCSI_OPCODE;
	}

	xop = kzalloc(sizeof(struct xcopy_op), GFP_KERNEL);
	if (!xop) {
		pr_err("Unable to allocate xcopy_op\n");
		return TCM_OUT_OF_RESOURCES;
	}
	xop->xop_se_cmd = se_cmd;

	p = transport_kmap_data_sg(se_cmd);
	if (!p) {
		pr_err("transport_kmap_data_sg() failed in target_do_xcopy\n");
		kfree(xop);
		return TCM_OUT_OF_RESOURCES;
	}

	list_id = p[0];
	list_id_usage = (p[1] & 0x18) >> 3;


	tdll = get_unaligned_be16(&p[2]);
	sdll = get_unaligned_be32(&p[8]);

	inline_dl = get_unaligned_be32(&p[12]);
	if (inline_dl != 0) {
		pr_err("XCOPY with non zero inline data length\n");
		goto out;
	}

	pr_debug("Processing XCOPY with list_id: 0x%02x list_id_usage: 0x%02x"
		" tdll: %hu sdll: %u inline_dl: %u\n", list_id, list_id_usage,
		tdll, sdll, inline_dl);

	rc = target_xcopy_parse_target_descriptors(se_cmd, xop, &p[16], tdll, &ret);
	if (rc <= 0)
		goto out;

	if (xop->src_dev->dev_attrib.block_size !=
	    xop->dst_dev->dev_attrib.block_size) {
		pr_err("XCOPY: Non matching src_dev block_size: %u + dst_dev"
		       " block_size: %u currently unsupported\n",
			xop->src_dev->dev_attrib.block_size,
			xop->dst_dev->dev_attrib.block_size);
		xcopy_pt_undepend_remotedev(xop);
		ret = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
		goto out;
	}

	pr_debug("XCOPY: Processed %d target descriptors, length: %u\n", rc,
				rc * XCOPY_TARGET_DESC_LEN);
	seg_desc = &p[16];
	seg_desc += (rc * XCOPY_TARGET_DESC_LEN);

	rc = target_xcopy_parse_segment_descriptors(se_cmd, xop, seg_desc, sdll);
	if (rc <= 0) {
		xcopy_pt_undepend_remotedev(xop);
		goto out;
	}
	transport_kunmap_data_sg(se_cmd);

	pr_debug("XCOPY: Processed %d segment descriptors, length: %u\n", rc,
				rc * XCOPY_SEGMENT_DESC_LEN);
	INIT_WORK(&xop->xop_work, target_xcopy_do_work);
	queue_work(xcopy_wq, &xop->xop_work);
	return TCM_NO_SENSE;

out:
	if (p)
		transport_kunmap_data_sg(se_cmd);
	kfree(xop);
	return ret;
}
