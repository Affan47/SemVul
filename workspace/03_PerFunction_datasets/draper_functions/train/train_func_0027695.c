searchPromptStatus(mail::searchParams &searchInfo)
{
	myServer::promptInfo prompt=
		myServer::prompt(myServer::promptInfo(_("Status: "))
				 .option(key_REPLIED,
					 Gettext::keyname(_("REPLIED_K:R")),
					 _("Replied"))

				 .option(key_DELETED,
					 Gettext::keyname(_("DELETED_K:D")),
					 _("Deleted"))

				 .option(key_UNREAD,
					 Gettext::keyname(_("UNREAD_K:U")),
					 _("Unread"))
				 );

	if (prompt.abortflag || myServer::nextScreen)
		return true;

	unicode_char promptKey=prompt.firstChar();

	if (promptKey == 0)
		return true;

	if (key_REPLIED == promptKey)
	{
		searchInfo.criteria=searchInfo.replied;
		return false;
	}

	if (key_DELETED == promptKey)
	{
		searchInfo.criteria=searchInfo.deleted;
		return false;
	}

	if (key_UNREAD == promptKey)
	{
		searchInfo.criteria=searchInfo.unread;
		return false;
	}
	return true;
}
