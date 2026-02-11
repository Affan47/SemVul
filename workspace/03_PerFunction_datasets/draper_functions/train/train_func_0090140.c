fdtv_get_ca_flags(struct firedtv_tuner_status *stat)
{
	int flags = 0;

	if (stat->ca_module_present_status == 1)
		flags |= CA_CI_MODULE_PRESENT;
	if (stat->ca_initialization_status == 1 &&
	    stat->ca_error_flag            == 0 &&
	    stat->ca_dvb_flag              == 1)
		flags |= CA_CI_MODULE_READY;
	return flags;
}
