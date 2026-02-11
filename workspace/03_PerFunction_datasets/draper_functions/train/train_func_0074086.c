htable_clear_internal(htable *tbl, BOOLEAN destroy, BOOLEAN destroy_nodes){
	if(!tbl) return;
	size_t i = 0;
	size_t processed = 0;
	for(; i < tbl->m_max_size; i++){
		if(tbl->m_array[i]){
			btree_iterator_in *it = btree_iterator_in_new(tbl->m_array[i]->root, &(btree_iterator_in){});
			if(destroy_nodes && destroy){
				for(btree *node = btree_iterator_in_next(it); node; node = btree_iterator_in_next(it)){
					CALL_VOID(((htable_node*)node->data)->data, destroy);
				}
			}
			btree_iterator_in_destroy(it);
			processed += tbl->m_array[i]->size;
	#ifdef SPLAY_PROCESS
			splay_clear(tbl->m_array[i], destroy_nodes);
			splaytree_destroy(tbl->m_array[i]);
	#else
			scapegoat_clear(tbl->m_array[i], destroy_nodes);
			scapegoat_destroy(tbl->m_array[i]);
	#endif
			tbl->m_array[i] = NULL;
			if(processed >= tbl->size) break;
		}
	}

	tbl->m_collision = 0;
	tbl->size = 0;
}
