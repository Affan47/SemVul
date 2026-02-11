gfire_group_is_by_purple_group(const gfire_group *p_group, const PurpleGroup *p_prpl_group)
{
	return (p_group && p_prpl_group && (p_group->group == p_prpl_group));
}
