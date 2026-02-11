readTopLevelFolders(mail::callback::folderList &callback1,
				     class mail::callback &callback2)
{
	vector<const mail::folder *> folder_list;

	if (magicInbox)
		folder_list.push_back( &inboxFolder );

	if (rootPath.size() > 0)
		folder_list.push_back( &hierarchyFolder );

	callback1.success(folder_list);
	callback2.success("OK");
}
