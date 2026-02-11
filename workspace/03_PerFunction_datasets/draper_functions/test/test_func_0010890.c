gfire_clan_check_for_left_members(gfire_clan *p_clan, gfire_data *p_gfire)
{
	if(!p_clan || !p_clan->prpl_group || !p_gfire)
		return;

	PurpleBlistNode *contact_buddy_node = purple_blist_node_get_first_child(PURPLE_BLIST_NODE(p_clan->prpl_group));
	if(!contact_buddy_node)
		return;

	PurpleBlistNode *buddy_node = NULL;

	while(contact_buddy_node)
	{
		gboolean in_contact = FALSE;

		if(!PURPLE_BLIST_NODE_IS_BUDDY(contact_buddy_node) && !PURPLE_BLIST_NODE_IS_CONTACT(contact_buddy_node))
		{
			contact_buddy_node = purple_blist_node_get_sibling_next(contact_buddy_node);
			continue;
		}

		else if(PURPLE_BLIST_NODE_IS_CONTACT(contact_buddy_node))
		{
			in_contact = TRUE;
			buddy_node = purple_blist_node_get_first_child(contact_buddy_node);

			if(!buddy_node)
				continue;
		}

		else
			buddy_node = contact_buddy_node;

		gboolean removed = FALSE;

		do
		{
			gboolean found = FALSE;
			PurpleBuddy *pbuddy = PURPLE_BUDDY(buddy_node);


			if(purple_buddy_get_account(pbuddy) != purple_connection_get_account(gfire_get_connection(p_gfire)))
				continue;


			GList *buddies = p_gfire->buddies;
			while(buddies)
			{

				if(!buddies->data)
				{
					buddies = g_list_next(buddies);
					continue;
				}


				gfire_buddy *gf_buddy = (gfire_buddy*)buddies->data;
				if(g_strcmp0(gf_buddy->name, purple_buddy_get_name(pbuddy)) == 0)
				{
					found = TRUE;
					break;
				}

				buddies = g_list_next(buddies);
			}


			if(!found)
			{
				purple_debug(PURPLE_DEBUG_INFO, "gfire", "%s seems to have left his clan, removing buddy\n", purple_buddy_get_name(pbuddy));


				if(in_contact)
				{
					buddy_node = purple_blist_node_get_sibling_next(buddy_node);
					if(!buddy_node)

						contact_buddy_node = purple_blist_node_get_sibling_next(contact_buddy_node);
				}
				else
					contact_buddy_node = purple_blist_node_get_sibling_next(contact_buddy_node);

				purple_blist_remove_buddy(pbuddy);

				removed = TRUE;
			}


		} while(in_contact && ((removed && buddy_node) ||
							   (!removed && (buddy_node = purple_blist_node_get_sibling_next(buddy_node)))));
		if(!removed)
			contact_buddy_node = purple_blist_node_get_sibling_next(contact_buddy_node);
	}
}
