ParseAsHPNonstop(CLine *pLine, CDirentry &entry)
{
	int index = 0;
	CToken token;


	if (!pLine->GetToken(index, token))
		return false;

	entry.name = token.GetString();


	if (!pLine->GetToken(++index, token))
		return false;
	if (!token.IsNumeric())
		return false;


	if (!pLine->GetToken(++index, token))
		return false;
	if (!token.IsNumeric())
		return false;

	entry.size = token.GetNumber();

	entry.flags = 0;


	if (!pLine->GetToken(++index, token))
		return false;
	if (!ParseShortDate(token, entry, false))
		return false;


	if (!pLine->GetToken(++index, token))
		return false;
	if (!ParseTime(token, entry))
		return false;


	if (!pLine->GetToken(++index, token))
		return false;
	entry.ownerGroup = token.GetString();

	if (token[token.GetLength() - 1] == ',')
	{

		if (!pLine->GetToken(++index, token))
			return false;
		entry.ownerGroup += _T(" ") + token.GetString();
	}


	if (!pLine->GetToken(++index, token))
		return false;
	entry.permissions = token.GetString();


	if (pLine->GetToken(++index, token))
		return false;

	return true;
}
