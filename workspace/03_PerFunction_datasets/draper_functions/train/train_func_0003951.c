xdg_ifree(char ***paths, char **fnames, int nopaths) {
	int i;

	if (paths != NULL) {
		if (*paths != NULL) {
			for (i = 0; i < nopaths; i++) {
				if ((*paths)[i] != NULL)
					free ((*paths)[i]);
			}
		}
		free(*paths);
		*paths = NULL;
	}
	if (fnames != NULL) {
		for (i = 0; i < nopaths; i++) {
			if (fnames[i] != NULL)
				free (fnames[i]);
		}
		free(fnames);
	}
}
