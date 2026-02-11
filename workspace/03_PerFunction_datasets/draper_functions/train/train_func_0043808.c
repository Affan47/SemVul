privileges_table_add_group (OobsGroup *group)
{
	const PrivilegeDescription *p;

	p = privilege_search (oobs_group_get_name (group));
	if (p == NULL)
		return;

	gtk_list_store_insert_with_values (privileges_model, NULL, G_MAXINT,
	                                   COL_MEMBER, FALSE,
	                                   COL_DESCRIPTION, (p) ? _(p->privilege) : NULL,
	                                   COL_GROUP, group,
	                                   -1);
}
