GMT_enforce_rgb_triplets (char *text, GMT_LONG size)
{


	GMT_LONG i, j, k = 0, n, last = 0, n_slash;
	int rgb[3];
	char buffer[BUFSIZ], color[16], *p = NULL;

	if (!strchr (text, '@')) return;

	while ((p = strstr (text, "@;"))) {
		i = (GMT_LONG)(p - text) + 2;
		for (j = last; j < i; j++, k++) buffer[k] = text[j];
		text[i-1] = 'X';
		if (text[i] != ';') {
			n = i;
			n_slash = 0;
			while (text[n] && text[n] != ';') {
				if (text[n] == '/') n_slash++;
				n++;
			}
			if (n_slash != 2) {
				text[n] = '\0';
				GMT_getrgb (&text[i], rgb);
				text[n] = ';';
				sprintf (color, "%d/%d/%d", rgb[0], rgb[1], rgb[2]);
				for (j = 0; color[j]; j++, k++) buffer[k] = color[j];
			}
			else
				for (j = i; j < n; j++, k++) buffer[k] = text[j];
			i = n;
		}
		buffer[k++] = ';';
		last = i + 1;
	}
	i = last;
	while (text[i]) buffer[k++] = text[i++];
	buffer[k++] = '\0';

	if (k > size) fprintf (stderr, "GMT_enforce_rgb_triplets: Replacement string too long - truncated\n");
	strncpy (text, buffer, (size_t)k);
}
