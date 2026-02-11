is_there_reiserfs_struct(char *fmt, int *what)
{
	char *k = fmt;

	while ((k = strchr(k, '%')) != NULL) {
		if (k[1] == 'k' || k[1] == 'K' || k[1] == 'h' || k[1] == 't' ||
		    k[1] == 'z' || k[1] == 'b' || k[1] == 'y' || k[1] == 'a') {
			*what = k[1];
			break;
		}
		k++;
	}
	return k;
}
