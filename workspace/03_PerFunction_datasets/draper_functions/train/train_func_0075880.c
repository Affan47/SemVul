setacl(const char *who, int flags)
{
	struct PCP *pcp=open_calendar();

	if (pcp_has_acl(pcp))
	{
		if (pcp_acl(pcp, who, flags))
		{
			error(pcp, 0, "pcp_acl");
			exit(1);
		}
	}
	else
	{
		fprintf(stderr, gettext("ERROR: ACLs not supported.\n"));
	}
	pcp_close(pcp);
}
