rb_init_rb_dlink_nodes(size_t dh_size)
{

	dnode_heap = rb_bh_create(sizeof(rb_dlink_node), dh_size, "librb_dnode_heap");
	if(dnode_heap == NULL)
		rb_outofmemory();
}
