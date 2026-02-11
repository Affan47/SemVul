gfire_buddy_prpl_remove(gfire_buddy *p_buddy)
{
	if(!p_buddy || !p_buddy->prpl_buddy)
		return;

	purple_blist_remove_buddy(p_buddy->prpl_buddy);
	p_buddy->prpl_buddy = NULL;
}
