GetUserHubList( CString nick )
{
	CStringList<DCTransferQueueObject> * StringList = 0;

	if ( pQueue->Get( nick, &StringList ) == 0 )
	{
		return StringList;
	}

	return 0;
}
