addrcache_person_remove_email( AddressCache *cache, ItemPerson *person, ItemEMail *email ) {
	ItemEMail *found = NULL;

	cm_return_val_if_fail( cache != NULL, NULL );

	if( person && email ) {
		found = addritem_person_remove_email( person, email );
		if( found ) {

			g_hash_table_foreach( cache->itemHash, addrcache_allgrp_rem_email_vis, email );


			if( person->listEMail ) {
				person->listEMail = g_list_remove( person->listEMail, email );
			}

			ADDRITEM_PARENT(email) = NULL;
			cache->dirtyFlag = TRUE;
		}
	}
	return found;
}
