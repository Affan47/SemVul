cmos_init(struct ibm_init_struct *iibm)
{
	int res;

	vdbg_printk(TPACPI_DBG_INIT,
		"initializing cmos commands subdriver\n");

	TPACPI_ACPIHANDLE_INIT(cmos);

	vdbg_printk(TPACPI_DBG_INIT, "cmos commands are %s\n",
		str_supported(cmos_handle != NULL));

	res = device_create_file(&tpacpi_pdev->dev, &dev_attr_cmos_command);
	if (res)
		return res;

	return (cmos_handle) ? 0 : 1;
}
