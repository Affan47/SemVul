splitdnarray(struct dnode **dn, int which)
{
	unsigned dncnt, d;
	struct dnode **dnp;

	if (dn == NULL)
		return NULL;


	dncnt = count_dirs(dn, which);


	dnp = dnalloc(dncnt);


	for (d = 0; *dn; dn++) {
		if (S_ISDIR((*dn)->dstat.st_mode)) {
			const char *name;

			if (!(which & (SPLIT_DIR|SPLIT_SUBDIR)))
				continue;
			name = (*dn)->name;
			if ((which & SPLIT_DIR)
			 || name[0]!='.' || (name[1] && (name[1]!='.' || name[2]))
			) {
				dnp[d++] = *dn;
			}
		} else if (!(which & (SPLIT_DIR|SPLIT_SUBDIR))) {
			dnp[d++] = *dn;
		}
	}
	return dnp;
}
