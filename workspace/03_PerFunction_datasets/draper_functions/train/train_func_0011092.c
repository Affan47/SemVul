mpt_Soft_Hard_ResetHandler(MPT_ADAPTER *ioc, int sleepFlag) {
	int ret = -1;

	ret = mpt_SoftResetHandler(ioc, sleepFlag);
	if (ret == 0)
		return ret;
	ret = mpt_HardResetHandler(ioc, sleepFlag);
	return ret;
}
