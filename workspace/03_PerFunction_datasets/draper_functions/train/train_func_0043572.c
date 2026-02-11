add_contact(const char *group, struct contact *user)
{
	grouplist *grp = find_grouplist_by_name(group);

	if (!grp) {
		add_group(group);
		grp = find_grouplist_by_name(group);
	}
	if (!grp) {
		eb_debug(DBG_CORE, "Error adding group :(\n");
		return;
	}
	grp->members = l_list_insert_sorted(grp->members, user, contact_cmp);
	user->group = grp;
}
