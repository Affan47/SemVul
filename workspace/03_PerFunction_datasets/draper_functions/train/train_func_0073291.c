kopt_setval(const char *name, char *val)
{
	int i;


	if (!strncmp("OPT_", name, 4))
		name += 4;

	for (i = 0; i < total_kopts; i++)
		if (!strcmp(KOPT[i].name, name)) {
			switch (KOPT[i].type) {
				case KOPT_BOOL:
					KOPT[i].def.b.v = val[0];
					break;
				case KOPT_TRISTATE:
					KOPT[i].def.t.v = val[0];
					break;
				case KOPT_INT:
					KOPT[i].def.i.v = atoi(val);
					break;
				case KOPT_STRING:
					KOPT[i].def.s.v = strdup(val);
					break;
			}
			KOPT[i].user_set++;
			return 0;
		}
	return -1;
}
