gth_tag_new_condition (GList *cond_list)
{
	GthTag *tag;

	tag = g_new0 (GthTag, 1);
	tag->type = GTH_TAG_IF;
	tag->value.cond_list = cond_list;

	return tag;
}
