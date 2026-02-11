rb_bh_gc_event(void *unused)
{
	rb_dlink_node *ptr;
	RB_DLINK_FOREACH(ptr, heap_lists->head)
	{
		rb_bh_gc(ptr->data);
	}
}
