pcap_setnonblock_mmap(pcap_t *p, int nonblock, char *errbuf)
{


	if (nonblock) {
		if (p->md.timeout >= 0) {


			p->md.timeout = p->md.timeout*-1 - 1;
		}
	} else {
		if (p->md.timeout < 0) {


			p->md.timeout = (p->md.timeout+1)*-1;
		}
	}
	return 0;
}
