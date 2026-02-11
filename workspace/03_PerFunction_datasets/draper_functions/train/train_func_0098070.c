saa7164_api_get_load_info(struct saa7164_dev *dev, struct tmFwInfoStruct *i)
{
	int ret;

	if (!(saa_debug & DBGLVL_CPU))
		return 0;

	dprintk(DBGLVL_API, "%s()\n", __func__);

	i->deviceinst = 0;
	i->devicespec = 0;
	i->mode = 0;
	i->status = 0;

	ret = saa7164_cmd_send(dev, 0, GET_CUR,
		GET_FW_STATUS_CONTROL, sizeof(struct tmFwInfoStruct), i);
	if (ret != SAA_OK)
		printk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	printk(KERN_INFO "saa7164[%d]-CPU: %d percent", dev->nr, i->CPULoad);

	return ret;
}
