set_page_opts(int page, display_data_t *display_data,
			  int count, char* initial_opts)
{
	page_opts_t *page_opts;
	ListIterator itr = NULL;
	char *col_name = NULL;

	xassert(page < PAGE_CNT);

	page_opts = &working_sview_config.page_opts[page];
	if (!page_opts->col_list) {
		page_opts->def_col_list = 1;
		page_opts->col_list = list_create(slurm_destroy_char);
		slurm_addto_char_list(page_opts->col_list, initial_opts);
	}

	page_opts->display_data = display_data;

	itr = list_iterator_create(page_opts->col_list);
	while ((col_name = list_next(itr))) {
		replus(col_name);
		if (strstr(col_name, "list")) {
			char *orig_ptr = col_name;
			xstrsubstitute(col_name, "bp ", "midplane");
			if (cluster_flags & CLUSTER_FLAG_BG)
				xstrsubstitute(col_name, "node", "midplane");
			else
				xstrsubstitute(col_name, "midplane", "node");


			if (col_name != orig_ptr) {
				list_insert(itr, col_name);


				list_remove(itr);
			}
		}
		while (display_data++) {
			if (display_data->id == -1)
				break;
			if (!display_data->name)
				continue;
			if (!strncasecmp(col_name, display_data->name,
					 strlen(col_name))) {
				display_data->show = TRUE;
				break;
			}
		}
		display_data = page_opts->display_data;
	}
	list_iterator_destroy(itr);
}
