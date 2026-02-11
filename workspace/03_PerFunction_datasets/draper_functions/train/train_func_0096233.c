logout(mail::callback &callback)
{
	if (!folderDirty)
	{
		callback.success("Mail folder closed.");
		return;
	}


	installTask(new ExpungeTask(*this, callback, false, NULL));
}
