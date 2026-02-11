dag_node_add_source_file(struct dag_node *n, const char *filename, char *remotename)
{
	struct dag_file *source = dag_file_lookup_or_create(n->d, filename);

	if(remotename)
		dag_node_add_remote_name(n, filename, remotename);


	list_push_head(n->source_files, source);


	list_push_head(source->needed_by, n);
}
