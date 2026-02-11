cell_comment_text_set (GnmComment *cc, char const *text)
{
	char *tmp;
	g_return_if_fail (IS_CELL_COMMENT (cc));

	tmp = g_strdup (text);
	g_free (cc->text);
	cc->text = tmp;
}
