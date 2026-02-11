tokenize_init (void)
{
	CamelHTMLParserPrivate *p;

	p = g_malloc (sizeof (*p));
	p->state = CAMEL_HTML_PARSER_DATA;

	p->attr = 0;
	p->attrs = g_ptr_array_new ();
	p->values = g_ptr_array_new ();
	p->tag = g_string_new ("");
	p->ent = g_string_new ("");
	p->charset = NULL;

	if (entities == NULL)
		tokenize_setup ();

	return p;
}
