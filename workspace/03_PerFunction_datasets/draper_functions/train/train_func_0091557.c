process_all( map_t tree,  struct avl_node *p, process_each_func f, void * param )
{
	if( tree->ret_code )
		return;

	if( p->avl_link[0] )
		process_all( tree, p->avl_link[0], f ,param );

	tree->ret_code |= f( param, p->key, p->val);

	if( p->avl_link[1] )
		process_all( tree, p->avl_link[1], f ,param );
}
