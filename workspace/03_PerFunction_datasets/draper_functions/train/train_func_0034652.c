ndmfhdb_add_fh_info_to_nlist (FILE *fp, ndmp9_name *nlist, int n_nlist)
{
	struct ndmfhdb		_fhcb, *fhcb = &_fhcb;
	int			i, rc, n_found;
	ndmp9_file_stat		fstat;

	rc = ndmfhdb_open (fp, fhcb);
	if (rc != 0) {
		return -31;
	}

	n_found = 0;

	for (i = 0; i < n_nlist; i++) {
		char *		name = nlist[i].original_path;

		rc = ndmfhdb_lookup (fhcb, name, &fstat);
		if (rc > 0) {
			nlist[i].fh_info = fstat.fh_info;
			if (fstat.fh_info.valid) {
				n_found++;
			}
		}
	}

	return n_found;
}
