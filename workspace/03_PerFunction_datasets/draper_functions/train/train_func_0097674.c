AddressBook_MenuInit( void )
{
	int i;

	memset(&s_addressbook_menu, 0, sizeof(s_addressbook_menu));

	s_addressbook_menu.x = viddef.width / 2 - 142;
	s_addressbook_menu.y = viddef.height / 2 - 58;
	s_addressbook_menu.nitems = 0;

	for ( i = 0; i < MAX_LOCAL_SERVERS; i++ )
	{
		cvar_t *adr;
		char buffer[20];

		Com_sprintf( buffer, sizeof( buffer ), "adr%d", i );

		adr = Cvar_Get( buffer, "", CVAR_ARCHIVE );

		s_addressbook_fields[i].generic.type = MTYPE_FIELD;
		s_addressbook_fields[i].generic.name = 0;
		s_addressbook_fields[i].generic.callback = 0;
		s_addressbook_fields[i].generic.x		= 0;
		s_addressbook_fields[i].generic.y		= i * 18 + 0;
		s_addressbook_fields[i].generic.localdata[0] = i;
		s_addressbook_fields[i].cursor			= 0;
		s_addressbook_fields[i].length			= 60;
		s_addressbook_fields[i].visible_length	= 30;

		strcpy( s_addressbook_fields[i].buffer, adr->string );

		Menu_AddItem( &s_addressbook_menu, &s_addressbook_fields[i] );
	}

	s_addressbook_menu.draw = AddressBook_MenuDraw;
	s_addressbook_menu.key = AddressBook_MenuKey;
}
