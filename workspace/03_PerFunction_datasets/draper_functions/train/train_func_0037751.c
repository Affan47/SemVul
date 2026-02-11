processXpatResponse(const char *l)
{
	if (*l == '.')
		done("OK");

	msgnum_t n;

	istringstream i(l);

	i >> n;

	if (i.fail() || myserver->index.size() == 0)
		return;

	if (lastIdxMsgNum == myserver->index.end())
		--lastIdxMsgNum;

	for (;;)
	{
		if (lastIdxMsgNum->msgNum > n)
		{
			if (lastIdxMsgNum == myserver->index.begin())
				break;
			--lastIdxMsgNum;
			if (lastIdxMsgNum->msgNum < n)
				break;
			continue;
		}
		else if (lastIdxMsgNum->msgNum < n)
		{
			if (++lastIdxMsgNum == myserver->index.end())
				break;
			if (lastIdxMsgNum->msgNum > n)
				break;
		}
		else
		{
			myserver->index[lastIdxMsgNum
					- myserver->index.begin()].msgFlag
				|= IDX_SEARCH;
			break;
		}
	}
}
