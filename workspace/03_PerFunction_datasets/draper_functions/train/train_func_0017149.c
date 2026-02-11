RT_LoadPrefs(GF_InputService *plug, RTPClient *rtp)
{
	const char *sOpt;

	sOpt = gf_modules_get_option((GF_BaseInterface *)plug, "Streaming", "DefaultPort");
	if (sOpt) {
		rtp->default_port = atoi(sOpt);
	} else {
		rtp->default_port = 554;
	}
	if ((rtp->default_port == 80) || (rtp->default_port == 8080))
		gf_modules_set_option((GF_BaseInterface *)plug, "Streaming", "RTPoverRTSP", "yes");

	sOpt = gf_modules_get_option((GF_BaseInterface *)plug, "Streaming", "RTPoverRTSP");
	if (sOpt && !stricmp(sOpt, "yes")) {
		rtp->transport_mode = 1;
	} else if (sOpt && !stricmp(sOpt, "OnlyCritical")) {
		rtp->transport_mode = 2;
	} else {
		rtp->transport_mode = 0;
	}


	sOpt = gf_modules_get_option((GF_BaseInterface *)plug, "Network", "UDPNotAvailable");
	if (sOpt && !stricmp(sOpt, "yes")) {
		if (!rtp->transport_mode) rtp->transport_mode = 1;

		gf_modules_set_option((GF_BaseInterface *)plug, "Network", "UDPNotAvailable", "no");
	}

	if (!rtp->transport_mode) {
		sOpt = gf_modules_get_option((GF_BaseInterface *)plug, "Network", "UDPTimeout");
		if (sOpt ) {
			rtp->udp_time_out = atoi(sOpt);
		} else {
			rtp->udp_time_out = 10000;
		}
	}

	sOpt = gf_modules_get_option((GF_BaseInterface *)plug, "Streaming", "RTSPTimeout");
	if (sOpt ) {
		rtp->time_out = atoi(sOpt);
	} else {
		rtp->time_out = 30000;
	}


	sOpt = gf_modules_get_option((GF_BaseInterface *)plug, "Streaming", "FirstPacketDrop");
	if (sOpt) {
		rtp->first_packet_drop = atoi(sOpt);
	} else {
		rtp->first_packet_drop = 0;
	}
	sOpt = gf_modules_get_option((GF_BaseInterface *)plug, "Streaming", "PacketDropFrequency");
	if (sOpt) {
		rtp->frequency_drop = atoi(sOpt);
	} else {
		rtp->frequency_drop = 0;
	}


}
