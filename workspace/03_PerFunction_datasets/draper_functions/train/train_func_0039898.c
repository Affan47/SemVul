ForgetRelationFsyncRequests(RelFileNode rnode)
{
	if (pendingOpsTable)
	{

		RememberFsyncRequest(rnode, FORGET_RELATION_FSYNC);
	}
	else if (IsUnderPostmaster)
	{


		while (!ForwardFsyncRequest(rnode, FORGET_RELATION_FSYNC))
			pg_usleep(10000L);


	}
}
