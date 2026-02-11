readSubFolders(mail::callback::folderList &callback1,
				      mail::callback &callback2)
	const
{
	if (isDestroyed(callback2))
		return;

	imapAccount.readSubFolders(path + hiersep, callback1, callback2);
}
