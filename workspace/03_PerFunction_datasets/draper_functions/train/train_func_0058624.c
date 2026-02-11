buildTab( UT_String & buffer )
{

	const gchar* szOld = _gatherTabEdit();
	bool res = UT_isValidDimensionString(szOld, MAX_TAB_LENGTH);
	if (res)
	{
		const gchar* szNew = UT_reformatDimensionString(m_dim, szOld);

		UT_String_sprintf( buffer, "%s/%c%c", szNew, AlignmentToChar(_gatherAlignment()),
		 					(static_cast<char>(_gatherLeader()))+'0');
	}

	return res;
}
