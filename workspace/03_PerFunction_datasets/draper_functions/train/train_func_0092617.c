addressbook_edit_person_flush_transient( void )
{
	ItemPerson *person = current_person;
	EditAddressPostUpdateCallback callback = edit_person_close_post_update_cb;


	current_abf = NULL;
	current_person = NULL;
	current_parent_folder = NULL;
	edit_person_close_post_update_cb = NULL;


	if (callback)
		callback( person );
}
