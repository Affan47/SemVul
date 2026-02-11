local_sig_destroy(unsigned int sig_id)
{
	unsigned int si;


	for (si = 0; ; si++) {
		if (si == sizeof(sig) / sizeof(sig[0])) {

			return;
		}
		if (! sig[si].type
		 || ! sig[si].name) {
			continue;
		}
		if (sig[si].id == sig_id) {

			break;
		}
	}

	if (sig[si].ptr) {

		system_sig_unget(sig[si].ptr);
	}

	free(sig[si].type);
	sig[si].type = NULL;

	free(sig[si].name);
	sig[si].name = NULL;
}
