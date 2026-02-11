deleteAllHosts() {
	host_element *h;
	int done = 0;
	while (!done) {
		h = pcurrent_host_element;
		if (h) {


			while (! deleteIcmpTest(h, h->pcurrent)) {}
		} else {
			done = 1;
		}


	}
}
