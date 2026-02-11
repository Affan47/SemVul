e_contact_map_google_with_evo_group (const gchar *group_name,
                                     gboolean google_to_evo)
{
	struct _GroupsMap {
		const gchar *google_id;
		const gchar *evo_name;
	} groups_map[] = {

		{ GDATA_CONTACTS_GROUP_CONTACTS,  N_("Personal") },

		{ GDATA_CONTACTS_GROUP_FRIENDS,   N_("Friends") },

		{ GDATA_CONTACTS_GROUP_FAMILY,    N_("Family") },

		{ GDATA_CONTACTS_GROUP_COWORKERS, N_("Coworkers") }
	};
	guint ii;

	if (!group_name)
		return NULL;

	for (ii = 0; ii < G_N_ELEMENTS (groups_map); ii++) {
		if (google_to_evo) {
			if (g_str_equal (group_name, groups_map[ii].google_id))
				return _(groups_map[ii].evo_name);
		} else {
			if (g_str_equal (group_name, _(groups_map[ii].evo_name)))
				return groups_map[ii].google_id;
		}
	}

	return NULL;
}
