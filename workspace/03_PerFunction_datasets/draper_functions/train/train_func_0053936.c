matchtcp(void* typedata1, void* typedata2) {

	const struct TCPListener *info1 = (struct TCPListener*)typedata1;
	const struct TCPListener *info2 = (struct TCPListener*)typedata2;

	return (info1->listenport == info2->listenport)
			&& (info1->chantype == info2->chantype)
			&& (strcmp(info1->listenaddr, info2->listenaddr) == 0);
}
