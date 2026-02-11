saa7164_api_get_fw_version(struct saa7164_dev *dev, u32 *version)
{
	int ret;

	ret = saa7164_cmd_send(dev, 0, GET_CUR,
		GET_FW_VERSION_CONTROL, sizeof(u32), version);
	if (ret != SAA_OK)
		printk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	return ret;
}
