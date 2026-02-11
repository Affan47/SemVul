gfire_buddy_set_common_buddies(gfire_buddy *p_buddy, GList *p_buddies)
{
	if(!p_buddy || !gfire_buddy_is_friend_of_friend(p_buddy))
		return;

	p_buddy->got_info = TRUE;

	if(p_buddy->common_buddies) gfire_list_clear(p_buddy->common_buddies);
	p_buddy->common_buddies = p_buddies;
}
