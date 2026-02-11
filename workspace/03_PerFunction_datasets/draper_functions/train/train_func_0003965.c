expando_get_signals(const char *key)
{
	EXPANDO_REC *rec;
	int *signals;
        int n;

	g_return_val_if_fail(key != NULL, NULL);

	rec = expando_find(key);
	if (rec == NULL || rec->signals < 0)
                return NULL;

	if (rec->signals == 0) {


		signals = g_new(int, 3);
		signals[0] = signal_get_uniq_id("expando timer");
		signals[1] = EXPANDO_ARG_NONE;
		signals[2] = -1;
                return signals;
	}

        signals = g_new(int, rec->signals*2+1);
	for (n = 0; n < rec->signals; n++) {
                signals[n*2] = rec->signal_ids[n];
                signals[n*2+1] = rec->signal_args[n];
	}
	signals[rec->signals*2] = -1;
        return signals;
}
