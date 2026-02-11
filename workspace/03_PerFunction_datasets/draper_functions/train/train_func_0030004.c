restoreSnapshot(mail::snapshot::restore &r)
{
	if (!i.is_open())
	{
		r.abortRestore();
		return;
	}

	size_t n;

	string l;

	for (n=0; n<nmessages; n++)
	{
		if (getline(i, l).fail())
		{
			cerr << (string)
				( Gettext(_("%1%: unable to read snapshot."))
				  << cachefile) << endl;
			r.abortRestore();
			return;
		}

		r.restoreIndex(n, mail::messageInfo(l));
	}

	while (!getline(i, l).fail())
	{
		{
			istringstream is(l);

			is >> n;

			if (is.fail() || n >= nmessages)
			{
				cerr << (string)
					( Gettext(_("%1%: unable to read"
						    " snapshot."))
					  << cachefile) << endl;
				r.abortRestore();
				return;
			}
		}

		set<string> kwset;

		for (;;)
		{
			if (getline(i, l).fail())
			{
				cerr << (string)
					( Gettext(_("%1%: unable to read"
						    " snapshot."))
					  << cachefile) << endl;
				r.abortRestore();
				return;
			}

			if (l.size() == 0)
				break;

			kwset.insert(l);
		}

		if (kwset.empty())
			continue;

		r.restoreKeywords(n, kwset);
	}
}
