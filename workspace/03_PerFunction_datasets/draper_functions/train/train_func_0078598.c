addrbook_add_group_list(AddressBookFile *book, ItemFolder *folder,
				   GList *listEMail)
{
	ItemGroup *group = NULL;
	ItemFolder *f = folder;

	cm_return_val_if_fail(book != NULL, NULL);

	if (!f)
		f = book->addressCache->rootFolder;
	group = addritem_create_item_group();
	addrcache_id_group(book->addressCache, group);
	addrcache_folder_add_group(book->addressCache, f, group);
	group->listEMail = listEMail;
	return group;
}
