ndmp_4to9_fh_add_dir_request (
  ndmp4_fh_add_dir_post *request4,
  ndmp9_fh_add_dir_request *request9)
{
	int			n_ent = request4->dirs.dirs_len;
	int			i;
	unsigned int		j;
	ndmp9_dir *		table;

	table = NDMOS_MACRO_NEWN(ndmp9_dir, n_ent);
	if (!table)
		return -1;

	NDMOS_API_BZERO (table, sizeof *table * n_ent);

	for (i = 0; i < n_ent; i++) {
		ndmp4_dir *		ent4 = &request4->dirs.dirs_val[i];
		ndmp4_file_name *	file_name;
		char *			filename;
		ndmp9_dir *		ent9 = &table[i];

		filename = "no-unix-name";
		for (j = 0; j < ent4->names.names_len; j++) {
			file_name = &ent4->names.names_val[j];
			if (file_name->fs_type == NDMP4_FS_UNIX) {
				filename =
				    file_name->ndmp4_file_name_u.unix_name;
				break;
			}
		}

		ent9->unix_name = NDMOS_API_STRDUP(filename);
		ent9->node = ent4->node;
		ent9->parent = ent4->parent;
	}

	request9->dirs.dirs_len = n_ent;
	request9->dirs.dirs_val = table;

	return 0;
}
