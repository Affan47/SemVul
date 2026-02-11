singleLineProcess(imap &imapAccount,
					 std::string &buffer)
{
	size_t p=buffer.find('\n');

	if (p == std::string::npos)
		return (0);

	setTimeout();

	++p;
	string buffer_cpy=buffer;
	buffer_cpy.erase(p);


	vector<const char *> words;

	string::iterator b=buffer_cpy.begin(), e=buffer_cpy.end();

	while (b != e)
	{
		if (unicode_isspace((unsigned char)*b))
		{
			b++;
			continue;
		}

		if (words.size() == 1)
		{
			if (strcmp(words[0], "+OK") == 0)
			{
				string s=string(b, e);

				while (s.size() > 0 &&
				       unicode_isspace((unsigned char)
					       s.end()[-1]))
					s.erase(s.end()-1, s.end());

				doDestroy=true;
				if (ok(fromutf8(s)))
				{
					if (doDestroy)
						imapAccount.
							uninstallHandler(this);
					return p;
				}
				return 0;
			}

			if (strcmp(words[0], "-ERR") == 0)
			{
				string s=string(b, e);

				while (s.size() > 0 &&
				       unicode_isspace((unsigned char)
					       s.end()[-1]))
					s.erase(s.end()-1, s.end());

				doDestroy=true;

				if (fail(fromutf8(s)))
				{
					if (doDestroy)
						imapAccount.
							uninstallHandler(this);
					return p;
				}
				return 0;
			}
		}

		words.push_back(&*b);

		if (*b != '"')
		{
			while (b != e && !unicode_isspace((unsigned char)*b))
				b++;

			if (b != e)
				*b++=0;
			continue;
		}


		string::iterator c=b;

		b++;

		while (b != e)
		{
			if (*b == '"')
			{
				b++;
				if (b == e || *b != '"')
					break;
			}
			*c++ = *b++;
		}
		*c=0;
	}
	if (!processLine(imapAccount, words))
		return 0;

	return p;
}
