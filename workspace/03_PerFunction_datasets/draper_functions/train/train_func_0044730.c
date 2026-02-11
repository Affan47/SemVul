signaler(int sig) {
    stop_flag++;
    if (cfg.verbose>2)
	fprintf(stderr,"\nSignal received.\n");
    pcap_close(cap);
}
