ekg_status_string(const int status, const int cmd)
{
	const char *r = NULL;

	if ((status > 0) && (status < (cmd == 2 ? 0x100 : 0x80))) {
		const struct ekg_status_info *s = status_find(status);

		if (s) {
			if (cmd == 1)
				r = s->command;
			if (!r)
				r = s->label;
		}
	}

	if (!r) {
		const struct ekg_status_info *s = status_find(cmd == 1 ? EKG_STATUS_AVAIL : EKG_STATUS_UNKNOWN);


		debug_error("ekg_status_string(): called with unexpected status: 0x%02x\n", status);
		if (!s) {
			debug_error("ekg_status_string(): critical error, status_find with predef value failed!\n");
			return NULL;
		}
		return (cmd == 1 ? s->command : s->label);
	}

	return r;
}
