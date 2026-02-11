setSyncMode(const uint8_t mode)
{
	CMT3LOG("L3: setSyncMode %u\n",(uint32_t) mode);
	CMT3EXITLOG;

	if (!isXm())
		return m_lastResult = XRV_INVALIDOPERATION;

	DO_DATA_SET_BID(CMT_MID_REQSYNCMODE,CMT_LEN_SYNCMODE,Byte,mode,CMT_BID_MASTER);
	return m_lastResult = XRV_OK;
}
