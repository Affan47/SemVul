setBaudrate(const uint32_t baudrate, bool reconnect)
{
	CMT3LOG("L3: setBaudrate %u %u\n",baudrate,reconnect?1:0);
	CMT3EXITLOG;

	uint8_t tmp;
	switch (baudrate)
	{
	case CMT_BAUD_RATE_9600:
		tmp = CMT_BAUDCODE_9K6;
		break;


	case CMT_BAUD_RATE_19K2:
		tmp = CMT_BAUDCODE_19K2;
		break;


	case CMT_BAUD_RATE_38K4:
		tmp = CMT_BAUDCODE_38K4;
		break;
	case CMT_BAUD_RATE_57K6:
		tmp = CMT_BAUDCODE_57K6;
		break;


	case CMT_BAUD_RATE_115K2:
		tmp = CMT_BAUDCODE_115K2;
		break;
	case CMT_BAUD_RATE_230K4:
		tmp = CMT_BAUDCODE_230K4;
		break;
	case CMT_BAUD_RATE_460K8:
		tmp = CMT_BAUDCODE_460K8;
		break;
	case CMT_BAUD_RATE_921K6:
		tmp = CMT_BAUDCODE_921K6;
		break;
	default:
		return m_lastResult = XRV_BAUDRATEINVALID;
	}

	if (baudrate != m_baudrate) {
		DO_DATA_SET_BID(CMT_MID_REQBAUDRATE,CMT_LEN_BAUDRATE,Byte,tmp,CMT_BID_MASTER);

		if (reconnect)
		{
			CMT3LOG("L3: sending reset for reconnect\n");

			Message sndReset(CMT_MID_RESET,0);
			Message rcvReset;
			sndReset.setBusId(CMT_BID_MASTER);
			m_serial.writeMessage(&sndReset);
			m_lastResult = m_serial.waitForMessage(&rcvReset,CMT_MID_RESETACK,0,false);
			if (m_lastResult != XRV_OK)
				return m_lastResult;
			if (m_logging)
				m_logFile.writeMessage(&rcvReset);
			bool wasMeasuring = m_measuring;
			m_measuring = true;

			CMT3LOG("L3: reopening port at new baud rate\n");
#ifdef _WIN32
			int32_t port;
			m_serial.getPortNr(port);
			closePort(false);
			m_lastResult = openPort(port,baudrate);
#else
			char portname[32];
			m_serial.getPortName(portname);
			closePort(false);
			m_lastResult = openPort(portname, baudrate);
#endif
			if (m_lastResult != XRV_OK)
				return m_lastResult;
			if (wasMeasuring)
				gotoMeasurement();
			return m_lastResult;
		}
	}

	return m_lastResult = XRV_OK;
}
