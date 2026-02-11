sort_tag_data (gconstpointer a,
	       gconstpointer b,
	       gpointer      user_data)
{
	TagData *tag_data_a = * (TagData **) a;
	TagData *tag_data_b = * (TagData **) b;

	if (tag_data_a->used && tag_data_b->used)
		return g_utf8_collate (tag_data_a->name, tag_data_b->name);
	else if (tag_data_a->used || tag_data_b->used)
		return tag_data_a->used ? -1 : 1;
	else if (tag_data_a->suggested && tag_data_b->suggested)
		return g_utf8_collate (tag_data_a->name, tag_data_b->name);
	else if (tag_data_a->suggested || tag_data_b->suggested)
		return tag_data_a->suggested ? -1 : 1;
	else
		return g_utf8_collate (tag_data_a->name, tag_data_b->name);
}
