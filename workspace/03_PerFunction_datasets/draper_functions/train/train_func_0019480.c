assign_session_replication_role(int newval, bool doit, GucSource source)
{


	if (doit && SessionReplicationRole != newval)
	{
		ResetPlanCache();
	}

	return true;
}
