fmtId(const char *rawid)
{


	static PQExpBuffer s_id_return = NULL;
	PQExpBuffer id_return;

	const char *cp;
	bool		need_quotes = false;

#ifdef WIN32
	if (parallel_init_done)
		id_return = (PQExpBuffer) TlsGetValue(tls_index);
	else
		id_return = s_id_return;
#else
	id_return = s_id_return;
#endif

	if (id_return)
	{

		resetPQExpBuffer(id_return);
	}
	else
	{

		id_return = createPQExpBuffer();
#ifdef WIN32
		if (parallel_init_done)
			TlsSetValue(tls_index, id_return);
		else
			s_id_return = id_return;
#else
		s_id_return = id_return;
#endif

	}


	if (quote_all_identifiers)
		need_quotes = true;

	else if (!((rawid[0] >= 'a' && rawid[0] <= 'z') || rawid[0] == '_'))
		need_quotes = true;
	else
	{

		for (cp = rawid; *cp; cp++)
		{
			if (!((*cp >= 'a' && *cp <= 'z')
				  || (*cp >= '0' && *cp <= '9')
				  || (*cp == '_')))
			{
				need_quotes = true;
				break;
			}
		}
	}

	if (!need_quotes)
	{


		const ScanKeyword *keyword = ScanKeywordLookup(rawid,
													   FEScanKeywords,
													   NumFEScanKeywords);

		if (keyword != NULL && keyword->category != UNRESERVED_KEYWORD)
			need_quotes = true;
	}

	if (!need_quotes)
	{

		appendPQExpBufferStr(id_return, rawid);
	}
	else
	{
		appendPQExpBufferChar(id_return, '\"');
		for (cp = rawid; *cp; cp++)
		{


			if (*cp == '\"')
				appendPQExpBufferChar(id_return, '\"');
			appendPQExpBufferChar(id_return, *cp);
		}
		appendPQExpBufferChar(id_return, '\"');
	}

	return id_return->data;
}
