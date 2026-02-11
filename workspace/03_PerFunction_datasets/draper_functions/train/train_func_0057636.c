addritem_person_add_email( ItemPerson *person, ItemEMail *email ) {
	GList *node;

	cm_return_val_if_fail( person != NULL, FALSE );
	cm_return_val_if_fail( email != NULL, FALSE );

	node = person->listEMail;
	while( node ) {
		if( node->data == email ) return FALSE;
		node = g_list_next( node );
	}
	person->listEMail = g_list_append( person->listEMail, email );
	ADDRITEM_PARENT(email) = ADDRITEM_OBJECT(person);
	return TRUE;
}
