show_pma_counter(struct ib_port *p, struct port_attribute *attr,
				char *buf)
{
	struct port_table_attribute *tab_attr =
		container_of(attr, struct port_table_attribute, attr);
	int offset = tab_attr->index & 0xffff;
	int width  = (tab_attr->index >> 16) & 0xff;
	struct ib_mad *in_mad  = NULL;
	struct ib_mad *out_mad = NULL;
	size_t mad_size = sizeof(*out_mad);
	u16 out_mad_pkey_index = 0;
	ssize_t ret;

	if (!p->ibdev->process_mad)
		return sprintf(buf, "N/A (no PMA)\n");

	in_mad  = kzalloc(sizeof *in_mad, GFP_KERNEL);
	out_mad = kmalloc(sizeof *out_mad, GFP_KERNEL);
	if (!in_mad || !out_mad) {
		ret = -ENOMEM;
		goto out;
	}

	in_mad->mad_hdr.base_version  = 1;
	in_mad->mad_hdr.mgmt_class    = IB_MGMT_CLASS_PERF_MGMT;
	in_mad->mad_hdr.class_version = 1;
	in_mad->mad_hdr.method        = IB_MGMT_METHOD_GET;
	in_mad->mad_hdr.attr_id       = cpu_to_be16(0x12);

	in_mad->data[41] = p->port_num;

	if ((p->ibdev->process_mad(p->ibdev, IB_MAD_IGNORE_MKEY,
		 p->port_num, NULL, NULL,
		 (const struct ib_mad_hdr *)in_mad, mad_size,
		 (struct ib_mad_hdr *)out_mad, &mad_size,
		 &out_mad_pkey_index) &
	     (IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_REPLY)) !=
	    (IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_REPLY)) {
		ret = -EINVAL;
		goto out;
	}

	switch (width) {
	case 4:
		ret = sprintf(buf, "%u\n", (out_mad->data[40 + offset / 8] >>
					    (4 - (offset % 8))) & 0xf);
		break;
	case 8:
		ret = sprintf(buf, "%u\n", out_mad->data[40 + offset / 8]);
		break;
	case 16:
		ret = sprintf(buf, "%u\n",
			      be16_to_cpup((__be16 *)(out_mad->data + 40 + offset / 8)));
		break;
	case 32:
		ret = sprintf(buf, "%u\n",
			      be32_to_cpup((__be32 *)(out_mad->data + 40 + offset / 8)));
		break;
	default:
		ret = 0;
	}

out:
	kfree(in_mad);
	kfree(out_mad);

	return ret;
}
