put_included(struct data *data, const char *path)
{
	if (data->ref_contents == NULL)
		data->ref_contents = strbuf_open(0);
	strbuf_puts0(data->ref_contents, path);
	data->ref_count++;
}
