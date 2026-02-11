main(int argc, char **argv)
{
    int num_workers = 1;
    char **ap = argv + 1;
    int x;
    int disable_greedy = 0;

    program_name = *argv;
    que_first = que_last = NULL;
    debug_level = get_env_debug_level();
    greedy_threshold = 0;

    while (*ap) {
	if (!strcmp(*ap, "-d")) {
	    ++debug_level;
	} else if(!strcmp(*ap, "-g") && *(ap + 1)) {
	    ++ap;
	    x = atoi(*ap);
	    if (!x) {
		usage(*ap);
	    } else {
		greedy_threshold = x;
	    }
	} else if(!strcmp(*ap, "-ng")) {
	    disable_greedy = 1;
	} else {
	    x = atoi(*ap);
	    if (!x) {
		usage(*ap);
	    } else {
		num_workers = x;
	    }
	}
	++ap;
    }

#ifdef WIN32
    if (num_workers > 60 || greedy_threshold > 60) {
	usage("More than 60 workers on windows impossible!");
	num_workers = 60;
	greedy_threshold = 0;
    }
#endif

    if(!greedy_threshold) {
	greedy_threshold = (3*num_workers)/4;
	if (!greedy_threshold) {
	    greedy_threshold = num_workers;
	}
    }

    if (disable_greedy) {
	greedy_threshold = num_workers + 1;
    }

#ifdef WIN32
    {
	WORD wr;
	WSADATA wsa_data;
	int wsa_error;
	wr = MAKEWORD(2,0);

	wsa_error = WSAStartup(wr,&wsa_data);
	if (wsa_error) {
	    fatal("Could not open usable winsock library.");
	}
	if (LOBYTE(wsa_data.wVersion) != 2 || HIBYTE(wsa_data.wVersion) != 0) {
	    fatal("Could not open recent enough winsock library.");
	}

	if (debug_level >= 1) {
	    do_allocate_console();

	    DEBUGF(1,("num_workers = %d, greedy_threshold = %d, "
		      "debug_level = %d.",
		      num_workers, greedy_threshold, debug_level));
	}
    }
    WAKEUP_WINSOCK();

#endif

    init_workers(num_workers);

    main_loop();
#ifndef WIN32
    kill_all_workers();
#endif
    return 0;
}
