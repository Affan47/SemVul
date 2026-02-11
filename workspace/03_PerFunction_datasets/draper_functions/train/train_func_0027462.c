expire_tgchange(void *unused)
{
	tgchange *target;
	rb_dlink_node *ptr, *next_ptr;

	RB_DLINK_FOREACH_SAFE(ptr, next_ptr, tgchange_list.head)
	{
		target = ptr->data;

		if(target->expiry < rb_current_time())
		{
			rb_dlinkDelete(ptr, &tgchange_list);
			rb_patricia_remove(tgchange_tree, target->pnode);
			rb_free(target->ip);
			rb_free(target);
		}
	}
}
