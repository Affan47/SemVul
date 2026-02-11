header_list_new (void)
{
	GMimeHeaderList *list;
	guint i;

	list = g_mime_header_list_new ();
	for (i = 0; i < G_N_ELEMENTS (initial); i++)
		g_mime_header_list_append (list, initial[i].name, initial[i].value);

	return list;
}
