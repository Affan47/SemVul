addritem_free_item_person( ItemPerson *person ) {
	cm_return_if_fail( person != NULL );


	g_free( ADDRITEM_ID(person) );
	g_free( ADDRITEM_NAME(person) );
	g_free( person->picture );
	g_free( person->firstName );
	g_free( person->lastName );
	g_free( person->nickName );
	g_free( person->externalID );
	g_list_free( person->listEMail );
	addritem_free_list_attribute( person->listAttrib );

	ADDRITEM_OBJECT(person)->type = ITEMTYPE_NONE;
	ADDRITEM_ID(person) = NULL;
	ADDRITEM_NAME(person) = NULL;
	ADDRITEM_PARENT(person) = NULL;
	ADDRITEM_SUBTYPE(person) = 0;
	person->picture = NULL;
	person->firstName = NULL;
	person->lastName = NULL;
	person->nickName = NULL;
	person->externalID = NULL;
	person->listEMail = NULL;
	person->listAttrib = NULL;

	g_free( person );
}
