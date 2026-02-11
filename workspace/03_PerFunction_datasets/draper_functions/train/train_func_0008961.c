report_iauth_conf(aClient *sptr, char *to)
{
	aExtCf *ectmp = iauth_conf;

	if (adfd < 0)
		return;
	while (ectmp)
	    {
		sendto_one(sptr, ":%s %d %s :%s",
			   ME, RPL_STATSIAUTH, to, ectmp->line);
		ectmp = ectmp->next;
	    }
}
