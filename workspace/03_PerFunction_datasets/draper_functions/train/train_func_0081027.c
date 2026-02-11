get_internaldate(mail::imap &imapAccount, Token t)
{
	if (t != ATOM && t != STRING)
	{
		error(imapAccount);
		return;
	}

	if (imapAccount.currentFetch)
	{


		string d=t.text;

		if (d[0] == ' ')
			d[0]='0';

		size_t spacepos=d.find(' ');
		size_t n;

		while ((n=d.find('-')) < spacepos)
			d[n]=' ';

		time_t tm=rfc822_parsedt(d.c_str());

		if (tm)
			imapAccount.currentFetch
				->messageArrivalDateCallback(count-1, tm);
	}

	next_func= &mail::imapFOLDER_COUNT::get_fetch_item;
}
