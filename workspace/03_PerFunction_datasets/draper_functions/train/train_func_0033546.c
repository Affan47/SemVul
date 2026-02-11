cm_store_increment_serial(void *parent, const char *old_serial)
{
	char *tmp, *serial;
	int len, i;
	if ((old_serial == NULL) || (strlen(old_serial) < 2)) {
		return talloc_strdup(parent, "01");
	}
	tmp = talloc_strdup(parent, old_serial);
	len = strlen(tmp);
	for (i = len - 1; i >= 0; i--) {
		switch (tmp[i]) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
			tmp[i]++;
			break;
		case '9':
			tmp[i] = 'A';
			break;
		case 'F':
		case 'f':
			tmp[i] = '0';

			continue;
			break;
		}

		break;
	}
	if (i < 0) {

		serial = talloc_asprintf(parent, "01%s", tmp);
		talloc_free(tmp);
	} else {
		if (strchr("89abcdefABCDEF", tmp[0]) != NULL) {

			serial = talloc_asprintf(parent, "00%s", tmp);
			talloc_free(tmp);
		} else {

			serial = tmp;
		}
	}
	return serial;
}
