setBluetoothState(const bool enabled)
{
	CMT3LOG("L3: setBluetoothState %u\n",enabled?1:0);
	CMT3EXITLOG;

	uint8_t dat = (enabled?0:1);
	DO_DATA_SET_BID(CMT_MID_REQBTDISABLE,CMT_LEN_BTDISABLE,Byte,dat,CMT_BID_MASTER);
	return m_lastResult = XRV_OK;
}
