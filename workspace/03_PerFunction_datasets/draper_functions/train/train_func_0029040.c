GetNewNetworkID(void)
{
    while (GET_BASE_OBJECT_FROM_ID(++startingOffset))
        ;
	if (startingOffset==UNASSIGNED_NETWORK_ID)
	{
		while (GET_BASE_OBJECT_FROM_ID(++startingOffset))
			;
	}
    return startingOffset;
}
