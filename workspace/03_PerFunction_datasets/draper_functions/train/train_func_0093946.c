resolve_port_argument(struct port_argument_s * n) {
    struct servent * s;

    if (n->port_min) {

	if ((s = getservbyname(n->port_min, NULL))) {
	    free(n->port_min);
	    asprintf(&n->port_min, "%d", ntohs(s->s_port));
	} else {


	    char * e;

	    strtol(n->port_min, &e, 10);
	    if (*e) {
		fprintf(stderr, "warning: suspicious port name encountered: %s\n", n->port_min);
	    }
	}
    }
    if (n->port_max) {

	if ((s = getservbyname(n->port_max, NULL))) {
	    free(n->port_max);
	    asprintf(&n->port_max, "%d", ntohs(s->s_port));
	} else {


	    char * e;

	    strtol(n->port_max, &e, 10);
	    if (*e) {
		fprintf(stderr, "warning: suspicious port name encountered: %s\n", n->port_max);
	    }
	}
    }
}
