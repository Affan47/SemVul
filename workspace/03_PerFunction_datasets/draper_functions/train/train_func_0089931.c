result_item_print_string_avrule(GtkTextBuffer * tb, GtkTextIter * iter, const char *s, unsigned int indent_level)
{
	const char *c, *next_c;
	const char *tag = NULL, *init_tag;
	unsigned int i;
	static const char *indent = "\t";
	for (i = 0; i < indent_level; i++) {
		gtk_text_buffer_insert(tb, iter, indent, -1);
	}
	for (c = s; *c && tag == NULL; c++) {
		switch (*c) {
		case '+':
		{
			tag = "added";
			break;
		}
		case '-':
		{
			tag = "removed";
			break;
		}
		case ' ':
		case '\t':
		case '\n':
		{
			break;
		}
		default:
		{
			tag = "modified";
			break;
		}
		}
	}
	init_tag = tag;
	c = strchr(s, '{');
	assert(c != NULL);


	c += 2;
	gtk_text_buffer_insert_with_tags_by_name(tb, iter, s, c - s, init_tag, NULL);
	while (*c != '}') {
		assert(*c != '\0');
		next_c = strchr(c, ' ');
		assert(next_c != NULL);
		switch (*c) {
		case '+':
		{
			tag = "added";
			break;
		}
		case '-':
		{
			tag = "removed";
			break;
		}
		default:
		{
			tag = init_tag;
		}
		}
		gtk_text_buffer_insert_with_tags_by_name(tb, iter, c, next_c - c, tag, "inline-link", NULL);
		gtk_text_buffer_insert_with_tags_by_name(tb, iter, " ", 1, init_tag, NULL);

		c = next_c + 1;
	}
	gtk_text_buffer_insert_with_tags_by_name(tb, iter, c, -1, init_tag, NULL);
}
