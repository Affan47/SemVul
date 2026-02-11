sbc_execute_unmap(struct se_cmd *cmd)
{
	struct sbc_ops *ops = cmd->protocol_data;
	struct se_device *dev = cmd->se_dev;
	unsigned char *buf, *ptr = NULL;
	sector_t lba;
	int size;
	u32 range;
	sense_reason_t ret = 0;
	int dl, bd_dl;


	if (cmd->t_task_cdb[1])
		return TCM_INVALID_CDB_FIELD;

	if (cmd->data_length == 0) {
		target_complete_cmd(cmd, SAM_STAT_GOOD);
		return 0;
	}

	if (cmd->data_length < 8) {
		pr_warn("UNMAP parameter list length %u too small\n",
			cmd->data_length);
		return TCM_PARAMETER_LIST_LENGTH_ERROR;
	}

	buf = transport_kmap_data_sg(cmd);
	if (!buf)
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	dl = get_unaligned_be16(&buf[0]);
	bd_dl = get_unaligned_be16(&buf[2]);

	size = cmd->data_length - 8;
	if (bd_dl > size)
		pr_warn("UNMAP parameter list length %u too small, ignoring bd_dl %u\n",
			cmd->data_length, bd_dl);
	else
		size = bd_dl;

	if (size / 16 > dev->dev_attrib.max_unmap_block_desc_count) {
		ret = TCM_INVALID_PARAMETER_LIST;
		goto err;
	}


	ptr = &buf[8];
	pr_debug("UNMAP: Sub: %s Using dl: %u bd_dl: %u size: %u"
		" ptr: %p\n", dev->transport->name, dl, bd_dl, size, ptr);

	while (size >= 16) {
		lba = get_unaligned_be64(&ptr[0]);
		range = get_unaligned_be32(&ptr[8]);
		pr_debug("UNMAP: Using lba: %llu and range: %u\n",
				 (unsigned long long)lba, range);

		if (range > dev->dev_attrib.max_unmap_lba_count) {
			ret = TCM_INVALID_PARAMETER_LIST;
			goto err;
		}

		if (lba + range > dev->transport->get_blocks(dev) + 1) {
			ret = TCM_ADDRESS_OUT_OF_RANGE;
			goto err;
		}

		ret = ops->execute_unmap(cmd, lba, range);
		if (ret)
			goto err;

		ptr += 16;
		size -= 16;
	}

err:
	transport_kunmap_data_sg(cmd);
	if (!ret)
		target_complete_cmd(cmd, GOOD);
	return ret;
}
