fe_checkcap(struct adapter_s *adapter) {
	char		*type="unknown";

	if (ioctl(adapter->fe.fd, IOCTL_GET_INFO, &adapter->fe.feinfo)) {
		logwrite(LOG_ERROR, "fe: ioctl(FE_GET_INFO...) failed");
		exit(-1);
	}

	switch(adapter->fe.feinfo.type) {
		case(FE_QPSK):
			type="QPSK";
			if (adapter->type == AT_DVBS)
				break;
			logwrite(LOG_ERROR, "fe: Adapter %d is an DVB-S card - config is not for DVB-S", adapter->no);
			exit(-1);
		case(FE_OFDM):
			type="OFDM";
			if (adapter->type == AT_DVBT)
				break;
			logwrite(LOG_ERROR, "fe: Adapter %d is an DVB-T card - config is not for DVB-T", adapter->no);
			exit(-1);
		case(FE_QAM):
			type="QAM";
			if (adapter->type == AT_DVBC)
				break;
			logwrite(LOG_ERROR, "fe: Adapter %d is an DVB-C card - config is not for DVB-C", adapter->no);
			exit(-1);
		default:
			logwrite(LOG_ERROR, "fe: Adapter %d is an unknown card type %d", adapter->no, adapter->fe.feinfo.type);
			break;
	}

	if (adapter->fe.feinfo.type == FE_QPSK && !(adapter->fe.feinfo.caps & FE_CAN_FEC_AUTO)) {
		logwrite(LOG_ERROR, "fe: adapter %d is incapable of handling FEC_AUTO - please report to flo@rfc822.org", adapter->no);
	}

	logwrite(LOG_DEBUG, "fe: adapter %d type %s name \"%s\"",
				adapter->no,
				type,
				adapter->fe.feinfo.name);

	logwrite(LOG_DEBUG, "fe: adapter %d frequency min %d max %d step %d tolerance %d",
				adapter->no,
				adapter->fe.feinfo.frequency_min,
				adapter->fe.feinfo.frequency_max,
				adapter->fe.feinfo.frequency_stepsize,
				adapter->fe.feinfo.frequency_tolerance);

	logwrite(LOG_DEBUG, "fe: adapter %d symbol rate min %d max %d tolerance %d",
				adapter->no,
				adapter->fe.feinfo.symbol_rate_min,
				adapter->fe.feinfo.symbol_rate_max,
				adapter->fe.feinfo.symbol_rate_tolerance);
}
