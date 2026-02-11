read_signal(DUH *duh, DUMBFILE *f)
{
	DUH_SIGNAL *signal;
	long type;

	signal = malloc(sizeof(*signal));

	if (!signal)
		return NULL;

	type = dumbfile_mgetl(f);
	if (dumbfile_error(f)) {
		free(signal);
		return NULL;
	}

	signal->desc = _dumb_get_sigtype_desc(type);
	if (!signal->desc) {
		free(signal);
		return NULL;
	}

	if (signal->desc->load_sigdata) {
		signal->sigdata = (*signal->desc->load_sigdata)(duh, f);
		if (!signal->sigdata) {
			free(signal);
			return NULL;
		}
	} else
		signal->sigdata = NULL;

	return signal;
}
