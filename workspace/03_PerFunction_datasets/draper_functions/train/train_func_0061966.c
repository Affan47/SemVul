M2TS_CanHandleURL(GF_InputService *plug, const char *url)
{
	char *sExt;
        if (!plug || !url)
          return 0;
	if (!strnicmp(url, "udp://", 6)
		|| !strnicmp(url, "mpegts-udp://", 13)
		|| !strnicmp(url, "mpegts-tcp://", 13)
#ifdef GPAC_HAS_LINUX_DVB
		|| !strnicmp(url, "dvb://", 6)
#endif
	) {
	  	return 1;
	}

	sExt = strrchr(url, '.');
	{
		int i=0;
		for (i = 0 ; NULL != MIMES[i]; i++)
			if (gf_term_check_extension(plug, MIMES[i], "ts m2t dmb", "MPEG-2 TS", sExt))
				return 1;
	}
	return 0;
}
