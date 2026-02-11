initOnce()
	{
		if(pglobalOptions->getListenerInterfaceCount()<1)
		  {
				CAMsg::printMsg(LOG_CRIT,"No Listener Interface spezified!\n");
				return E_UNKNOWN;
			}

		bCapturePackets = bReplayPackets = false;
		#if defined(REPLAY_DETECTION)&&!defined(_WIN32)

			signal(SIGUSR1, SIGUSR1_handler);
			signal(SIGUSR2, SIGUSR2_handler);
		#endif

		UINT8 strTarget[255];
		if(pglobalOptions->getMixHost(strTarget,255)!=E_SUCCESS)
		  {
				CAMsg::printMsg(LOG_CRIT,"No AnonServer specified!\n");
				return E_UNKNOWN;
			}
		return E_SUCCESS;
	}
