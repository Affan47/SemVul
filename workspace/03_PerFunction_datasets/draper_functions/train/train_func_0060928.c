cleanup() {


        if (pcap_hnd) pcap_breakloop(pcap_hnd);
        if (rate_stats) cleanup_rate_stats();

        fflush(NULL);

        free_format();
        free_methods();
        if (buf) free(buf);


        if (daemon_mode) remove(pid_filename);
        if (pcap_hnd) pcap_close(pcap_hnd);

        return;
}
