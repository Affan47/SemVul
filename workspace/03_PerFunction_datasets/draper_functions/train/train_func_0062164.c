libmail_mimeheader_free(struct mime_header *m)
{
	struct mime_attribute *a;

	while ((a=m->attr_list) != 0)
	{
		m->attr_list=a->next;
		if (a->name)
			free(a->name);
		if (a->value)
			free(a->value);
		free(a);
	}
	free(m->header_name);
	free(m);
}
