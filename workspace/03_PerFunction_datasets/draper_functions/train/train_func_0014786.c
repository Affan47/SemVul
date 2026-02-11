pcap_lookupdev(errbuf)
	register char *errbuf;
{
	pcap_if_t *alldevs;

#ifndef IF_NAMESIZE
#define IF_NAMESIZE IFNAMSIZ
#endif
	static char device[IF_NAMESIZE + 1];
	char *ret;

	if (pcap_findalldevs(&alldevs, errbuf) == -1)
		return (NULL);

	if (alldevs == NULL || (alldevs->flags & PCAP_IF_LOOPBACK)) {


		(void)strlcpy(errbuf, "no suitable device found",
		    PCAP_ERRBUF_SIZE);
		ret = NULL;
	} else {


		(void)strlcpy(device, alldevs->name, sizeof(device));
		ret = device;
	}

	pcap_freealldevs(alldevs);
	return (ret);
}
