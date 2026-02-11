handshake_autoprobe_fragsize(int dns_fd)
{
	char in[4096];
	int i;
	int read;
	int proposed_fragsize = 768;
	int range = 768;
	int max_fragsize;

	max_fragsize = 0;
	fprintf(stderr, "Autoprobing max downstream fragment size... (skip with -m fragsize)\n");
	while (running && range > 0 && (range >= 8 || max_fragsize < 300)) {

		for (i=0; running && i<3 ;i++) {

			send_fragsize_probe(dns_fd, proposed_fragsize);

			read = handshake_waitdns(dns_fd, in, sizeof(in), 'r', 'R', 1);


				if (read > 0) {

					if (fragsize_check(in, read, proposed_fragsize, &max_fragsize) == 1)
						break;
				}


			fprintf(stderr, ".");
			fflush(stderr);
		}
		if (max_fragsize < 0)
			break;

		range >>= 1;
		if (max_fragsize == proposed_fragsize) {

			proposed_fragsize += range;
		} else {

			fprintf(stderr, "%d not ok.. ", proposed_fragsize);
			fflush(stderr);
			proposed_fragsize -= range;
		}
	}
	if (!running) {
		fprintf(stderr, "\n");
		warnx("stopped while autodetecting fragment size (Try setting manually with -m)");
		return 0;
	}
	if (max_fragsize <= 2) {


		fprintf(stderr, "\n");
		warnx("found no accepted fragment size.");
		warnx("try setting -M to 200 or lower, or try other -T or -O options.");
		return 0;
	}

	fprintf(stderr, "will use %d-2=%d\n", max_fragsize, max_fragsize - 2);


	if (max_fragsize < 82) {
		fprintf(stderr, "Note: this probably won't work well.\n");
		fprintf(stderr, "Try setting -M to 200 or lower, or try other DNS types (-T option).\n");
	} else if (max_fragsize < 202 &&
	    (do_qtype == T_NULL || do_qtype == T_TXT ||
	     do_qtype == T_SRV || do_qtype == T_MX)) {
		fprintf(stderr, "Note: this isn't very much.\n");
		fprintf(stderr, "Try setting -M to 200 or lower, or try other DNS types (-T option).\n");
	}

	return max_fragsize - 2;
}
