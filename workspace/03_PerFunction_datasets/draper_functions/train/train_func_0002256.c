ndmp_3to9_fh_add_dir_free_request (ndmp9_fh_add_dir_request *request9)
{
    int	i;

    if (request9) {
	if(request9->dirs.dirs_val) {
	    int n_ent = request9->dirs.dirs_len;

	    for (i = 0; i < n_ent; i++) {
		ndmp9_dir *ent9 = &request9->dirs.dirs_val[i];
		if (ent9->unix_name)
		    NDMOS_API_FREE(ent9->unix_name);
		ent9->unix_name = 0;
	    }

	    NDMOS_API_FREE(request9->dirs.dirs_val);
	}
	request9->dirs.dirs_val = 0;
    }
    return 0;
}
