auto_pool_print_table_header(FILE * s, struct pool_table_header *h)
{
	while(h->name) {
		char *n = xxmalloc(h->width + 1);
		fill_string(h->name, n, h->width, h->align);
		string_toupper(n);
		printf("%s ", n);
		free(n);
		h++;
	}
	printf("\n");
}
