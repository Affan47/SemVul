showHelp(FILE *f)
{
	int i = 0;
	while (strhelp[i] != NULL) {
		for (unsigned int j = 0; j < (get_len() - 2); j++) {
			if (strhelp[i] == NULL) break;
			fprintf(f, "%s",strhelp[i++]);
		}
		if (strhelp[i] != NULL) pressenkey(f);
	}
}
