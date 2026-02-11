png_add_text (const char *keyword, const char *text)
{
	struct png_text *pt;

	pt = malloc (sizeof(struct png_text));
	if (pt == 0)
		return 0;

	pt->length = strlen(keyword) + strlen(text) + 1;
	pt->data = malloc (pt->length + 1);
	if (pt->data == 0)
		return 0;

	strcpy (pt->data, keyword);
	strcpy (pt->data + strlen(keyword) + 1, text);
	pt->next = png_text_list;
	png_text_list = pt;

	return 1;
}
