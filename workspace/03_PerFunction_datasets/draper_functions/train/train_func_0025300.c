sym_tab_add_id(

	sym_tab_t*	sym_tab,
	byte*		name,
	ulint		len)
{
	sym_node_t*	node;

	node = mem_heap_alloc(sym_tab->heap, sizeof(sym_node_t));

	node->common.type = QUE_NODE_SYMBOL;

	node->resolved = FALSE;
	node->indirection = NULL;

	node->name = mem_heap_strdupl(sym_tab->heap, (char*) name, len);
	node->name_len = len;

	UT_LIST_ADD_LAST(sym_list, sym_tab->sym_list, node);

	dfield_set_null(&node->common.val);

	node->common.val_buf_size = 0;
	node->prefetch_buf = NULL;
	node->cursor_def = NULL;

	node->sym_table = sym_tab;

	return(node);
}
