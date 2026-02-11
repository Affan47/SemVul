new_styleset(guint file_type_id, gsize styling_count)
{
	StyleSet *set = &style_sets[file_type_id];

	set->count = styling_count;
	set->styling = g_new0(GeanyLexerStyle, styling_count);
}
