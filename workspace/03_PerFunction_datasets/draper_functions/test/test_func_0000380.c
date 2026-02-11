getDataLength(uint32_t& length, const CmtDeviceId deviceId)
{
	CMT3LOG("L3: getDataLength %08x\n",deviceId);
	CMT3EXITLOG;

	DO_DATA_REQUEST(CMT_MID_REQDATALENGTH);
	length = rcv.getDataShort();
	return m_lastResult = XRV_OK;
}
