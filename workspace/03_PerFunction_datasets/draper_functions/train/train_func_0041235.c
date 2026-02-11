OpenSource() {
	char errstr[STATUS_MAX] = "";
	last_channel = 0;
	char *unconst = strdup(interface.c_str());

	pd = pcap_open_live(unconst, MAX_PACKET_LEN, 1, 1000, errstr);

	free(unconst);

	if (strlen(errstr) > 0 || pd == NULL) {
		globalreg->messagebus->InjectMessage(errstr, MSGFLAG_ERROR);
		return 0;
	}

	error = 0;

	paused = 0;
	errstr[0] = '\0';
	num_packets = 0;


    #if defined (SYS_OPENBSD) || defined(SYS_NETBSD) || defined(SYS_FREEBSD) \
		|| defined(SYS_DARWIN)


	pcap_set_datalink(pd, DLT_IEEE802_11);
	pcap_set_datalink(pd, DLT_IEEE802_11_RADIO_AVS);
	pcap_set_datalink(pd, DLT_IEEE802_11_RADIO);


	ioctl(pcap_get_selectable_fd(pd), BIOCPROMISC, NULL);


	int v = 1;
	ioctl(pcap_get_selectable_fd(pd), BIOCIMMEDIATE, &v);
	#endif

	if (DatalinkType() < 0) {
		pcap_close(pd);
		return -1;
	}

#ifdef HAVE_PCAP_NONBLOCK
    pcap_setnonblock(pd, 1, errstr);
#elif !defined(SYS_OPENBSD) && defined(HAVE_PCAP_GETSELFD)

    int save_mode = fcntl(pcap_get_selectable_fd(pd), F_GETFL, 0);
    if (fcntl(pcap_get_selectable_fd(pd), F_SETFL, save_mode | O_NONBLOCK) < 0) {
        snprintf(errstr, 1024, "fcntl failed, errno %d (%s)",
                 errno, strerror(errno));
    }
#endif

	if (strlen(errstr) > 0) {
		globalreg->messagebus->InjectMessage(errstr, MSGFLAG_ERROR);

		if (pd != NULL)
			pcap_close(pd);

		return 0;
	}

	return 1;
}
