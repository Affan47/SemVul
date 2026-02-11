save_log(void)
{
	FILE *f;
	struct network *n = _state.s_networks.n_next;

	f = fopen(_conf.cf_log, "w");
	if (!f)
		err(1, "fopen()");

	fprintf(f, "# SSID              ");
	fprintf(f, "| KEY                                    | BSSID");
	fprintf(f, "             | MAC filter\n");

	while (n) {
		save_network(f, n);
		n = n->n_next;
	}

	fclose(f);
}
