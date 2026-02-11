gfire_purple_remove_group(PurpleConnection *p_gc, PurpleGroup *p_group)
{
	if(!p_gc || !p_group)
		return;

	gfire_group *group = gfire_find_group(p_gc->proto_data, p_group, GFFG_PURPLE);
	if(group)
	{
		gfire_remove_group(p_gc->proto_data, group, TRUE);
	}
}
