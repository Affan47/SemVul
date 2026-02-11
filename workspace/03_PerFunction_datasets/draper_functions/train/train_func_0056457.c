cleanup_dir(const char *dir, size_t maxfiles, size_t maxsize)
{
	unsigned i;

	cc_log("Cleaning up cache directory %s", dir);

	object_size_threshold = maxsize * LIMIT_MULTIPLE;
	object_files_threshold = maxfiles * LIMIT_MULTIPLE;

	num_files = 0;
	total_object_files = 0;
	total_object_size = 0;


	traverse(dir, traverse_fn);


	sort_and_clean();

	stats_set_sizes(dir, total_object_files, total_object_size);


	for (i = 0; i < num_files; i++) {
		free(files[i]->fname);
		free(files[i]);
		files[i] = NULL;
	}
	if (files) {
		free(files);
	}
	allocated = 0;
	files = NULL;

	num_files = 0;
	total_object_files = 0;
	total_object_size = 0;
}
