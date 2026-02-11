locked(mail::file
							&lockedFile)
{


	if (me.path == me.mboxAccount->currentFolder && mboxAccount.currentFolderReadOnly)
	{
		me.fail("Folder opened in read-only mode.");
		done();
		return true;
	}

	me.copyTo(lockedFile);
	done();
	return true;
}
