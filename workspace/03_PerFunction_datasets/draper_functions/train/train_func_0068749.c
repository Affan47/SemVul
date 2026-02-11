cap_gen_bitfield(fd_set *bf){
	struct capt *netif;
	int fd, max = 0;

	netif = first_capt;
	while(netif != NULL){
		fd = pcap_fileno(netif->pcap);
		FD_SET(fd, bf);
		if(fd > max) max = fd;
		netif = netif->next;
	}
	return(max);
}
