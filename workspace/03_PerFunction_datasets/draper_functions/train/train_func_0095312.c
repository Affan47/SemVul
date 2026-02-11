check_class()
{
	struct Class *cltmp;
	rb_dlink_node *ptr;
	rb_dlink_node *next_ptr;

	RB_DLINK_FOREACH_SAFE(ptr, next_ptr, class_list.head)
	{
		cltmp = ptr->data;

		if(MaxUsers(cltmp) < 0)
		{
			rb_dlinkDestroy(ptr, &class_list);
			if(CurrUsers(cltmp) <= 0)
				free_class(cltmp);
		}
	}
}
