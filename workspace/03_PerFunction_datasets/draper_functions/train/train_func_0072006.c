processLine(imap &imapAccount,
				 vector<const char *> &words)
{
	if (words.size() >= 2 &&
	    strcmp(words[0], "*") == 0 &&
	    strcasecmp(words[1], "SEARCH") == 0)
	{
		vector<const char *>::iterator b=words.begin()+2,
			e=words.end();

		while (b != e)
		{
			size_t first=0;
			size_t last=0;
			char dummy=0;

			string w(*b++);
			istringstream i(w);

			i >> first >> dummy >> last;

			if (dummy != '-')
				last=first;

			if (first == 0 || last == 0 || last < first)
				continue;
			--first;
			--last;

			do
			{
				if (first >=
				    (imapAccount.currentFolder ?
				     imapAccount.currentFolder->exists:0))
					break;
				found.push_back(first);
			} while (first++ < last);
		}
		return true;
	}
	return smapHandler::processLine(imapAccount, words);
}
