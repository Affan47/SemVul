sigqueue_list(ulong sigqueue) {
        ulong sigqueue_save, next;
	int sig;
	char *signal_buf;
	long size;
        size = VALID_SIZE(signal_queue) ?  SIZE(signal_queue) : SIZE(sigqueue);
        signal_buf = GETBUF(size);

        sigqueue_save = sigqueue;
        while (sigqueue) {
        	readmem(sigqueue, KVADDR, signal_buf,
			SIZE_OPTION(signal_queue, sigqueue),
			"signal_queue/sigqueue", FAULT_ON_ERROR);

		if (VALID_MEMBER(signal_queue_next) &&
		    VALID_MEMBER(signal_queue_info)) {
                	next = ULONG(signal_buf + OFFSET(signal_queue_next));
                	sig = INT(signal_buf + OFFSET(signal_queue_info) +
				 OFFSET(siginfo_si_signo));
		} else {
			next = ULONG(signal_buf +
                        	OFFSET_OPTION(sigqueue_next, sigqueue_list));
                	sig = INT(signal_buf + OFFSET(sigqueue_info) +
				OFFSET(siginfo_si_signo));
		}

		if (sigqueue_save == next)
			break;

                fprintf(fp, "             %3d  %lx\n",
                        sig, sigqueue +
			OFFSET_OPTION(signal_queue_info, sigqueue_info));

                sigqueue = next;
        }
	FREEBUF(signal_buf);

}
