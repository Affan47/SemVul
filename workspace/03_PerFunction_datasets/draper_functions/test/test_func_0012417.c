ndmp_9to2_fh_add_unix_dir_request (
  ndmp9_fh_add_dir_request *request9,
  ndmp2_fh_add_unix_dir_request *request2)
{
	int			n_ent = request9->dirs.dirs_len;
	int			i;
	ndmp2_fh_unix_dir *		table;

	table = NDMOS_MACRO_NEWN(ndmp2_fh_unix_dir, n_ent);
	if (!table)
		return -1;

	NDMOS_API_BZERO (table, sizeof *table * n_ent);

	for (i = 0; i < n_ent; i++) {
		ndmp9_dir *		ent9 = &request9->dirs.dirs_val[i];
		ndmp2_fh_unix_dir *	ent2 = &table[i];

		CNVT_STRDUP_FROM_9x (ent2, ent9, name, unix_name);
		CNVT_FROM_9 (ent2, ent9, node);
		CNVT_FROM_9 (ent2, ent9, parent);
	}

	request2->dirs.dirs_len = n_ent;
	request2->dirs.dirs_val = table;

	return 0;
}
