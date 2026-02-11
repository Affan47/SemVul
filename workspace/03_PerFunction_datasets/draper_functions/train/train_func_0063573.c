setSeed (graph_t * G, int dflt, long* seedp)
{
    char smallbuf[32];
    char *p = agget(G, "start");
    int init = dflt;

    if (!p || (*p == '\0')) return dflt;
    if (isalpha(*(unsigned char *)p)) {
	if (!strncmp(p, SMART, SLEN(SMART))) {
	    init = INIT_SELF;
	    p += SLEN(SMART);
	} else if (!strncmp(p, REGULAR, SLEN(REGULAR))) {
	    init = INIT_REGULAR;
	    p += SLEN(REGULAR);
	} else if (!strncmp(p, RANDOM, SLEN(RANDOM))) {
	    init = INIT_RANDOM;
	    p += SLEN(RANDOM);
	}
	else init = dflt;
    }
    else if (isdigit(*(unsigned char *)p)) {
	init = INIT_RANDOM;
    }

    if (init == INIT_RANDOM) {
	long seed;

	if (!isdigit(*(unsigned char *)p) || sscanf(p, "%ld", &seed) < 1) {
#if defined(MSWIN32) || defined(WIN32)
	    seed = (unsigned) time(NULL);
#else
	    seed = (unsigned) getpid() ^ (unsigned) time(NULL);
#endif
	    sprintf(smallbuf, "%ld", seed);
	    agset(G, "start", smallbuf);
	}
	*seedp = seed;
    }
    return init;
}
