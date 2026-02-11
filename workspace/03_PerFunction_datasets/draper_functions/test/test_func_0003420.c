addrbook_parse_member(AddressBookFile *book, XMLFile *file,
				  ItemGroup *group)
{
	GList *attr;
	gchar *name, *value;
	gchar *eid = NULL;

	ItemEMail *email = NULL;

	attr = xml_get_current_tag_attr(file);
	while (attr) {
		name = ((XMLAttr *)attr->data)->name;
		value = ((XMLAttr *)attr->data)->value;
		if( strcmp( name, AB_ATTAG_EID ) == 0 )
			eid = g_strdup( value );
		attr = g_list_next(attr);
	}

	email = addrcache_get_email(book->addressCache, eid);
	g_free(eid);
	if (email) {
		if (group) {
			addrcache_group_add_email(book->addressCache, group,
						  email);
		}
		else {
			addritem_free_item_email(email);
			email = NULL;
		}
	}
}
