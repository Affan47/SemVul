ndmp_9to3_fh_add_file_request (
  ndmp9_fh_add_file_request *request9,
  ndmp3_fh_add_file_request *request3)
{
	int			n_ent = request9->files.files_len;
	int			i;
	ndmp3_file *		table;

	table = NDMOS_MACRO_NEWN(ndmp3_file, n_ent);
	if (!table)
		return -1;

	NDMOS_API_BZERO (table, sizeof *table * n_ent);

	for (i = 0; i < n_ent; i++) {
		ndmp9_file *		ent9 = &request9->files.files_val[i];
		ndmp3_file *		ent3 = &table[i];

		ent3->names.names_val = NDMOS_MACRO_NEW(ndmp3_file_name);
		ent3->names.names_len = 1;
		ent3->stats.stats_val = NDMOS_MACRO_NEW(ndmp3_file_stat);
		ent3->stats.stats_len = 1;

		ent3->names.names_val[0].fs_type = NDMP3_FS_UNIX;
		ent3->names.names_val[0].ndmp3_file_name_u.unix_name =
				NDMOS_API_STRDUP(ent9->unix_path);

		ndmp_9to3_file_stat (&ent9->fstat,
				&ent3->stats.stats_val[0]);
		ent3->node = ent9->fstat.node.value;
		ent3->fh_info = ent9->fstat.fh_info.value;
	}

	request3->files.files_len = n_ent;
	request3->files.files_val = table;

	return 0;
}
