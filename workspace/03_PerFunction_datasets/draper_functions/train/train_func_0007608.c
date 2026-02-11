dumpPortList() {
	int done = 0;
	if (!pfirst_host_element) {
		printf("ERROR002: PortScanner::dumpPortList called while hostlist was empty.  It's a bug, sorry!\n");
		exit(1);
	}
	struct host_element *h = pfirst_host_element->pnext;
	dumpHostList();
	printf("--- Start of portlist dump ---\n");
	while (!done) {
		printf("\tPortlist dump for %s:\n", inet_ntoa(h->ip));
		struct port_element *pp;
		pp = h->pfirst_port;

		while(pp != h->plast_port) {
			printf("\t\tport=%d, send_count=%d ptr addr=%lx", pp->port, pp->send_count, (unsigned long int)pp);
			if (pp == h->pcurrent_port) {
				printf(" <- current_port");
			}
			if (pp == h->pfirst_port) {
				printf(" <- first_port");
			}
			if (pp == h->plast_port) {
				printf(" <- last_port");
			}
			printf("\n");
			pp = pp->pnext;
		}
		printf("\t\tport=%d, send_count=%d ptr addr=%lx", pp->port, pp->send_count, (unsigned long int)pp);
		if (pp == h->pcurrent_port) {
			printf(" <- current_port");
		}
		if (pp == h->pfirst_port) {
			printf(" <- first_port");
		}
		if (pp == h->plast_port) {
			printf(" <- last_port");
		}
		printf("\n");


		if (h == pfirst_host_element) {
			done = 1;
		} else {
			h = h->pnext;
		}
	}
	printf("--- End of portlist dump ---\n");
}
