MultiXactIdIsCurrent(MultiXactId multi)
{
	bool		result = false;
	TransactionId *members;
	int			nmembers;
	int			i;

	nmembers = GetMultiXactIdMembers(multi, &members);

	if (nmembers < 0)
		return false;

	for (i = 0; i < nmembers; i++)
	{
		if (TransactionIdIsCurrentTransactionId(members[i]))
		{
			result = true;
			break;
		}
	}

	pfree(members);

	return result;
}
