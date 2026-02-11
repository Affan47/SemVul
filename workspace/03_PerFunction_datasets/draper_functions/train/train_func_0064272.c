getSyncOutPulseWidth(uint32_t& pulseWidth)
{
	CMT3LOG("L3: getSyncOutPulseWidth\n");
	CMT3EXITLOG;

	Message snd(CMT_MID_REQSYNCOUTSETTINGS,1);
	Message rcv;

	snd.setBusId(CMT_BID_MASTER);

	snd.setDataByte(CMT_PARAM_SYNCOUT_PULSEWIDTH);
	m_serial.writeMessage(&snd);
	m_lastResult = m_serial.waitForMessage(&rcv,CMT_MID_REQSYNCOUTSETTINGSACK,0,true);
	if (m_lastResult != XRV_OK)
		return m_lastResult;
	if (m_logging)
		m_logFile.writeMessage(&rcv);
	HANDLE_ERR_RESULT;
	pulseWidth = rcv.getDataLong(1);


	pulseWidth = (uint32_t)	((((double)pulseWidth)*CMT_SYNC_CLOCK_TICKS_TO_NS)+0.5);

	return m_lastResult = XRV_OK;
}
