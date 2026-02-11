make_new_load_table()
{
    Trans_table *tr_tbl;

    if(sche_info->load_head == NULL){
	sche_info->load_head = alloc_trans_table();

	return sche_info->load_head;
    }else{
	for (tr_tbl = sche_info->load_head;
	     tr_tbl->next != NULL;
	     tr_tbl = tr_tbl->next){}
	tr_tbl->next = alloc_trans_table();
	tr_tbl->next->prev = tr_tbl;
	tr_tbl = tr_tbl->next;

	return tr_tbl;
    }
}
