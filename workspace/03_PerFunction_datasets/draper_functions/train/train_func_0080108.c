create_toc_string(mb_disc_private *d, char *sep) {
	char tmp[16];
	char *toc;
	int i, size;

	assert( d != NULL );


	size = 1 + d->last_track_num - d->first_track_num;

	size += 3;

	size *= (6 + strlen(sep));

	size++;

	toc = calloc(size, sizeof(char));
	if (!toc) return NULL;

	sprintf(toc, "%d%s%d%s%d",
			d->first_track_num,
			sep,
			d->last_track_num,
			sep,
			d->track_offsets[0]);

	for (i = d->first_track_num; i <= d->last_track_num; i++) {
		sprintf(tmp, "%s%d", sep, d->track_offsets[i]);
		strcat(toc, tmp);
	}

	return toc;
}
