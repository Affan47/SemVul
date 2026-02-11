init_active_list()
{
	int i;
	ss_active_item	*sai;

	Assert( Ss_pool != NULL );

	clear_active_list();


	for ( i = 0; i < MAX_SHIP_CLASSES; i++ ) {
		if ( Ss_pool[i] > 0 ) {
			sai = get_free_active_list_node();
			if ( sai != NULL ) {
				sai->ship_class = i;
				list_append(&SS_active_head, sai);
				SS_active_list_size++;
			}
		}
	}
}
