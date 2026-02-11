abc_init(void *alloc_f_api(int size),
	      void free_f_api(void *ptr),
	      void level_f_api(int level),
	      int client_sz_api,
	      int keep_comment_api)
{
	if (alloc_f != 0) {
		fprintf(stderr, "abc_init already initialized\n");
		return;
	}
	alloc_f = alloc_f_api;
	free_f = free_f_api;
	level_f = level_f_api;
	client_sz = client_sz_api;
	keep_comment = keep_comment_api;
}
