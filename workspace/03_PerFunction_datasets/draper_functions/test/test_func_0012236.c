fs_commit(fs_backend *be, fs_segment seg, int force_trans)
{
    fs_rid_set *rs = NULL;

    if (fs_list_length(be->pending_delete) > 0) {
	rs = fs_rid_set_new();
	fs_rid val;
	fs_list_rewind(be->pending_delete);
	while (fs_list_next_value(be->pending_delete, &val)) {
	    fs_rid_set_add(rs, val);
	}
    }

    if (be->pended_import) {


	fs_rid quad[4];
	fs_rid pred = FS_RID_NULL;
	fs_ptree *current_tree = NULL;
	for (int i=0; i<FS_PENDED_LISTS; i++) {
	    fs_list_flush(be->pended[i]);


	    fs_list_rewind(be->pended[i]);
	    fs_list_sort_chunked(be->pended[i], quad_sort_by_psmo);
	    while (fs_list_next_sort_uniqed(be->pended[i], quad)) {
		if (quad[2] != pred) {
		    pred = quad[2];
		    current_tree = fs_backend_get_ptree(be, pred, 0);
		    if (!current_tree) {

			int n = fs_backend_open_ptree(be, pred);
			struct ptree_ref *r = fs_backend_ptree_ref(be, n);
			current_tree = r->ptree_s;
			fs_list_add(be->predicates, &pred);
		    }
		    if (!current_tree) {
			fs_error(LOG_CRIT, "failed to create ptree for %016llx",
				 pred);
		    }
		}
		fs_rid pair[2] = { quad[0], quad[3] };
		fs_ptree_add(current_tree, quad[1], pair, 0);
	    }


	    pred = FS_RID_NULL;
	    current_tree = NULL;
	    fs_list_rewind(be->pended[i]);
	    fs_list_sort_chunked(be->pended[i], quad_sort_by_poms);
	    while (fs_list_next_sort_uniqed(be->pended[i], quad)) {
		if (quad[2] != pred) {
		    pred = quad[2];
		    current_tree = fs_backend_get_ptree(be, pred, 1);
		    if (!current_tree) {
			fs_error(LOG_CRIT, "failed to get ptree for %016llx",
				 pred);
		    }
		}
		fs_rid pair[2] = { quad[0], quad[1] };
		fs_ptree_add(current_tree, quad[3], pair, 0);
	    }


	    fs_list_unlink(be->pended[i]);
	    fs_list_close(be->pended[i]);
	    be->pended[i] = NULL;
	}

	be->pended_import = 0;
    }

    if (rs) {
	fs_rid_set_free(rs);
    }

    return 0;
}
