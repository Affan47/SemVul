et_insert_text (AtkEditableText *text,
                const gchar *string,
                gint length,
                gint *position)
{

	gchar *result;

	const gchar *full_text = et_get_full_text (ATK_TEXT (text));
	if (full_text == NULL)
		return;

	result = g_strdup_printf (
		"%.*s%.*s%s", *position, full_text,
		length, string, full_text + *position);

	et_set_full_text (text, result);

	*position += length;

	g_free (result);
}
