asd_clear_aca(struct domain_device *dev, u8 *lun)
{
	int res = asd_initiate_ssp_tmf(dev, lun, TMF_CLEAR_ACA, 0);

	if (res == TMF_RESP_FUNC_COMPLETE)
		asd_clear_nexus_I_T_L(dev, lun);
	return res;
}
