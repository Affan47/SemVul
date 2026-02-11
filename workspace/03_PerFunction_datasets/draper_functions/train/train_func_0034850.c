saa7164_api_enum_subdevs(struct saa7164_dev *dev)
{
	int ret;
	u32 buflen = 0;
	u8 *buf;

	dprintk(DBGLVL_API, "%s()\n", __func__);


	ret = saa7164_cmd_send(dev, 0, GET_LEN,
		GET_DESCRIPTORS_CONTROL, sizeof(buflen), &buflen);
	if (ret != SAA_OK)
		printk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	dprintk(DBGLVL_API, "%s() total descriptor size = %d bytes.\n",
		__func__, buflen);


	buf = kzalloc(buflen, GFP_KERNEL);
	if (!buf)
		return SAA_ERR_NO_RESOURCES;


	ret = saa7164_cmd_send(dev, 0, GET_CUR,
		GET_DESCRIPTORS_CONTROL, buflen, buf);
	if (ret != SAA_OK) {
		printk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);
		goto out;
	}

	if (saa_debug & DBGLVL_API)
		print_hex_dump(KERN_INFO, "", DUMP_PREFIX_OFFSET, 16, 1, buf,
			       buflen & ~15, false);

	saa7164_api_dump_subdevs(dev, buf, buflen);

out:
	kfree(buf);
	return ret;
}
