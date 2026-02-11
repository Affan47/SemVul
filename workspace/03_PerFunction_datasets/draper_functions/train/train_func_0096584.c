inotifytools_initialize_stats() {
	niceassert( init, "inotifytools_initialize not called yet" );


	if (collect_stats) {
		rbwalk(tree_wd, empty_stats, 0);
	}

	num_access = 0;
	num_modify = 0;
	num_attrib = 0;
	num_close_nowrite = 0;
	num_close_write = 0;
	num_open = 0;
	num_move_self = 0;
	num_moved_from = 0;
	num_moved_to = 0;
	num_create = 0;
	num_delete = 0;
	num_delete_self = 0;
	num_unmount = 0;
	num_total = 0;

	collect_stats = 1;
}
