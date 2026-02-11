goNextLine(const c8* buf, const c8* const bufEnd)
{

	while(buf != bufEnd)
	{

		if (*buf=='\n' || *buf=='\r')
			break;
		++buf;
	}
	return goFirstWord(buf, bufEnd);
}
