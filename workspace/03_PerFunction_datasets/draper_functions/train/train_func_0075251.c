MultiXactIdExpand(MultiXactId multi, TransactionId xid, MultiXactStatus status)
{
	MultiXactId newMulti;
	MultiXactMember *members;
	MultiXactMember *newMembers;
	int			nmembers;
	int			i;
	int			j;

	AssertArg(MultiXactIdIsValid(multi));
	AssertArg(TransactionIdIsValid(xid));


	Assert(MultiXactIdIsValid(OldestMemberMXactId[MyBackendId]));

	debug_elog5(DEBUG2, "Expand: received multi %u, xid %u status %s",
				multi, xid, mxstatus_to_string(status));


	nmembers = GetMultiXactIdMembers(multi, &members, false, false);

	if (nmembers < 0)
	{
		MultiXactMember member;


		member.xid = xid;
		member.status = status;
		newMulti = MultiXactIdCreateFromMembers(1, &member);

		debug_elog4(DEBUG2, "Expand: %u has no members, create singleton %u",
					multi, newMulti);
		return newMulti;
	}


	for (i = 0; i < nmembers; i++)
	{
		if (TransactionIdEquals(members[i].xid, xid) &&
			(members[i].status == status))
		{
			debug_elog4(DEBUG2, "Expand: %u is already a member of %u",
						xid, multi);
			pfree(members);
			return multi;
		}
	}


	newMembers = (MultiXactMember *)
		palloc(sizeof(MultiXactMember) * (nmembers + 1));

	for (i = 0, j = 0; i < nmembers; i++)
	{
		if (TransactionIdIsInProgress(members[i].xid) ||
			(ISUPDATE_from_mxstatus(members[i].status) &&
			 TransactionIdDidCommit(members[i].xid)))
		{
			newMembers[j].xid = members[i].xid;
			newMembers[j++].status = members[i].status;
		}
	}

	newMembers[j].xid = xid;
	newMembers[j++].status = status;
	newMulti = MultiXactIdCreateFromMembers(j, newMembers);

	pfree(members);
	pfree(newMembers);

	debug_elog3(DEBUG2, "Expand: returning new multi %u", newMulti);

	return newMulti;
}
