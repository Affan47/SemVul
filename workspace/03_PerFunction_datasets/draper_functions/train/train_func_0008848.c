set_slave_adapters(char *o)
{
	int i, j, la, a_id, a_id2;
	char buf[100], *arg[20], *sep;
	adapter *ad;
	strncpy(buf, o, sizeof(buf));
	la = split(arg, buf, sizeof(arg), ',');
	for (i = 0; i < la; i++)
	{
		a_id = map_intd(arg[i], NULL, -1);
		if (a_id < 0 || a_id >= MAX_ADAPTERS)
			continue;

		sep = strchr(arg[i], '-');
		a_id2 = a_id;
		if (sep)
			a_id2 = map_intd(sep + 1, NULL, -1);

		if (a_id2 < 0 || a_id2 >= MAX_ADAPTERS)
			continue;

		for (j = a_id; j <= a_id2; j++)
		{
			if (!a[j])
				a[j] = adapter_alloc();

			ad = a[j];
			ad->diseqc_param.switch_type = SWITCH_SLAVE;

			LOGL(0, "Setting slave adapter %d", j);
		}

	}
}
