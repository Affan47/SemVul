xdl_fill_merge_buffer(xdfenv_t *xe1, const char *name1,
		xdfenv_t *xe2, const char *name2, xdmerge_t *m, char *dest)
{
	const int marker_size = 7;
	int marker1_size = (name1 ? strlen(name1) + 1 : 0);
	int marker2_size = (name2 ? strlen(name2) + 1 : 0);
	int conflict_marker_size = 3 * (marker_size + 1)
		+ marker1_size + marker2_size;
	int size, i1, j;

	for (size = i1 = 0; m; m = m->next) {
		if (m->mode == 0) {
			size += xdl_recs_copy(xe1, i1, m->i1 - i1, 0,
					dest ? dest + size : NULL);
			if (dest) {
				for (j = 0; j < marker_size; j++)
					dest[size++] = '<';
				if (marker1_size) {
					dest[size] = ' ';
					memcpy(dest + size + 1, name1,
							marker1_size - 1);
					size += marker1_size;
				}
				dest[size++] = '\n';
			} else
				size += conflict_marker_size;
			size += xdl_recs_copy(xe1, m->i1, m->chg1, 1,
					dest ? dest + size : NULL);
			if (dest) {
				for (j = 0; j < marker_size; j++)
					dest[size++] = '=';
				dest[size++] = '\n';
			}
			size += xdl_recs_copy(xe2, m->i2, m->chg2, 1,
					dest ? dest + size : NULL);
			if (dest) {
				for (j = 0; j < marker_size; j++)
					dest[size++] = '>';
				if (marker2_size) {
					dest[size] = ' ';
					memcpy(dest + size + 1, name2,
							marker2_size - 1);
					size += marker2_size;
				}
				dest[size++] = '\n';
			}
		} else if (m->mode == 1)
			size += xdl_recs_copy(xe1, i1, m->i1 + m->chg1 - i1, 0,
					dest ? dest + size : NULL);
		else if (m->mode == 2)
			size += xdl_recs_copy(xe2, m->i2 - m->i1 + i1,
					m->i1 + m->chg2 - i1, 0,
					dest ? dest + size : NULL);
		else
			continue;
		i1 = m->i1 + m->chg1;
	}
	size += xdl_recs_copy(xe1, i1, xe1->xdf2.nrec - i1, 0,
			dest ? dest + size : NULL);
	return size;
}
