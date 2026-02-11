signaler(int sig) {
    if (!stop_flag)
	pcap_close(cap);
    stop_flag++;
    if (cfg.verbose>2)
	fprintf(stderr,"\nSignal received.\n");
}
