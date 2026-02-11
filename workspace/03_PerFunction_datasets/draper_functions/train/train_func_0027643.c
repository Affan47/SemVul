searchNickname(std::string nickname,
						  std::vector<
						  mail::emailAddress>
						  &addrListArg)
{
	addrListArg.clear();

	if (!search)
		return true;

	std::string k=Gettext::toutf8(nickname);

	callback_info info;

	info.addrList= &addrListArg;
	info.cnt=0;

	int rc=l_search_do(search, k.c_str(), callback_func, &info);

	if (rc == 1)
	{
		statusBar->clearstatus();

		statusBar->status(Gettext(_("Discarded additional matches on %1%"))
				  << nickname);
		statusBar->beepError();
		rc=0;
	}

	if (rc != 0)
		return false;

	return true;
}
