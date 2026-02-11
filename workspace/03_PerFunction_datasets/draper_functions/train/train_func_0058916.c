destroy_channel(struct Channel *chptr)
{
	rb_dlink_node *ptr, *next_ptr;

	RB_DLINK_FOREACH_SAFE(ptr, next_ptr, chptr->invites.head)
	{
		del_invite(chptr, ptr->data);
	}


	free_channel_list(&chptr->banlist);
	free_channel_list(&chptr->exceptlist);
	free_channel_list(&chptr->invexlist);
	free_channel_list(&chptr->quietlist);


	free_topic(chptr);

	rb_dlinkDelete(&chptr->node, &global_channel_list);
	del_from_channel_hash(chptr->chname, chptr);
	free_channel(chptr);
}
