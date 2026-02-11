copy_sync_table_list(Sync_table *sync_head)
{
    Sync_table *ypt;
    Sync_table *new_ypt;
    Sync_table *new_head = NULL, *new_tail = NULL;

    for (ypt = sync_head; ypt; ypt = ypt->next) {
	new_ypt = copy_sync_table(ypt);
	if (!new_head) {
	    new_head = new_ypt;
	}else{
	    new_tail->next = new_ypt;
	}
	new_tail = new_ypt;
    }

    return(new_head);
}
