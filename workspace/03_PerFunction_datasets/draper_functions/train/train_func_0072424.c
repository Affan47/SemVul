ShowSummary(ostream &out)
{

	char * key;
	int num_cookies = 0;

	cookieDict->Start_Get();

	out << endl << "Cookies that have been correctly imported from: " << _filename << endl;

	while ((key = cookieDict->Get_Next()))
	{
		List * list;
		HtCookie * cookie;

		list = (List *)cookieDict->Find(key);
		list->Start_Get();

		while ((cookie = (HtCookie *)list->Get_Next()))
		{
			++num_cookies;
			out << "  " << num_cookies << ". " << cookie->GetName()
				<< ": " << cookie->GetValue() << " (Domain: " << cookie->GetDomain();
			if (debug > 1)
			{
				out << " - Path: " << cookie->GetPath();
				if (cookie->GetExpires())
					out << " - Expires: " << cookie->GetExpires()->GetRFC850();
			}
			out << ")" << endl;
		}


	}

	return out;

}
