sprintf_percent(char **fmt, int *fmtl, char **b, char *blimit, eval_scalar *s)
{
	char cfmt[32];
	char buf[512];
	int ci=1;
	cfmt[0]='%';
	while (*fmtl && ci < 32-1) {
		cfmt[ci]=(*fmt)[0];
		cfmt[ci+1]=0;
		switch ((*fmt)[0]) {
			case 'd':
			case 'i':
			case 'o':
			case 'u':
			case 'x':
			case 'X':
			case 'c': {
				eval_int i;
				scalar_context_int(s, &i);

				ht_snprintf(buf, sizeof buf, cfmt, i.value);
				sprintf_puts(b, blimit, buf);

				return 1;
			}
			case 's': {
				char *q=cfmt+1;
				eval_str t;
				scalar_context_str(s, &t);

				while (*q!='s') {
					if ((*q>='0') && (*q<='9')) {
						unsigned int sl=strtol(q, NULL, 10);
						if (sl>sizeof buf-1) sl=sizeof buf-1;
						sprintf(q, "%ds", sl);
						break;
					} else {
						switch (*q) {
							case '+':
							case '-':
							case '#':
							case ' ':
								break;
							default:

								break;
						}
					}
					q++;
				}

				if ((unsigned int)t.len>sizeof buf-1) t.len=sizeof buf-1;
				t.value[t.len]=0;

				ht_snprintf(buf, sizeof buf, cfmt, t.value);

				sprintf_puts(b, blimit, buf);

				string_destroy(&t);
				return 1;
			}
			case 'e':
			case 'E':
			case 'f':
			case 'F':
			case 'g':
			case 'G': {
				eval_float f;
				scalar_context_float(s, &f);

				ht_snprintf(buf, sizeof buf, cfmt, f.value);
				sprintf_puts(b, blimit, buf);

				return 1;
			}
			case '%':
				sprintf_puts(b, blimit, "%");
				return 1;
		}
		(*fmt)++;
		(*fmtl)--;
		ci++;
	}
	return 0;
}
