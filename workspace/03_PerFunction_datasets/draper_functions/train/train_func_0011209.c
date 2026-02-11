eel_accessibility_text_get_character_at_offset (AtkText *text,
						gint     offset)
{
	char *txt, *index;
	gint sucks1 = 0, sucks2 = -1;
	gunichar c;
	GailTextUtil *util = get_simple_text (text);
	g_return_val_if_fail (util != NULL, 0);

	txt = gail_text_util_get_substring (util, sucks1, sucks2);

	index = g_utf8_offset_to_pointer (txt, offset);
	c = g_utf8_get_char (index);
	g_free (txt);

	return c;
}
