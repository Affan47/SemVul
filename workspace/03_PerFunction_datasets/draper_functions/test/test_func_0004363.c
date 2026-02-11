addrcache_add_contact(
		AddressCache *cache, ItemFolder *folder, const gchar *name,
		const gchar *address, const gchar *remarks )
{
	ItemPerson *person = NULL;
	ItemEMail *email = NULL;
	ItemFolder *f = folder;

	cm_return_val_if_fail( cache != NULL, NULL );

	if( ! f ) f = cache->rootFolder;


	person = addritem_create_item_person();
	addritem_person_set_common_name( person, name );
	addrcache_id_person( cache, person );
	addrcache_folder_add_person( cache, f, person );


	email = addritem_create_item_email();
	addritem_email_set_address( email, address );
	addritem_email_set_remarks( email, remarks );
	addrcache_id_email( cache, email );
	addritem_person_add_email( person, email );
	cache->dirtyFlag = TRUE;

	return person;
}
