storeXkfState(const CmtDeviceId deviceId)
{
	CMT3LOG("L3: storeXkfState %08x\n",deviceId);
	CMT3EXITLOG;

	uint8_t bid = getBusIdInternal(deviceId);
	if (bid == CMT_BID_INVALID || bid == CMT_BID_BROADCAST)
		return (m_lastResult = XRV_INVALIDID);

	Message	snd(CMT_MID_STOREXKFSTATE,CMT_LEN_STOREXKFSTATE);
	Message rcv;

	snd.setBusId(bid);
	m_serial.writeMessage(&snd);
	m_lastResult = m_serial.waitForMessage(&rcv,CMT_MID_STOREXKFSTATEACK,0,true);
	if (m_lastResult != XRV_OK)
		return m_lastResult;
	if (m_logging)
		m_logFile.writeMessage(&rcv);
	if (rcv.getMessageId() == CMT_MID_ERROR)
	{
		m_lastHwErrorDeviceId = m_config.m_masterDeviceId;
		if (rcv.getDataSize() >= 2)
		{
			uint8_t biddy = rcv.getDataByte(1);
			getDeviceId(biddy,m_lastHwErrorDeviceId);
		}
		return m_lastResult = m_lastHwError = (XsensResultValue) rcv.getDataByte();
	}
	return m_lastResult = XRV_OK;
}
