bundler_rename(struct dag_node *n, const char *filename)
{

	if(n) {
		struct list *input_files = dag_input_files(n->d);
		if(list_find(input_files, (int (*)(void *, const void *)) string_equal, (void *) filename)) {
			list_free(input_files);
			return xxstrdup(filename);
		}
	}
	return bundler_translate_name(filename, 0);
}
