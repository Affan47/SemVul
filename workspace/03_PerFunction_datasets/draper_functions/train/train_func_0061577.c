uid_discard_new_list(struct query *ctl)
{

    if (outlevel >= O_DEBUG)
    {


	report_build(stdout, GT_("Merged UID list from %s:"), ctl->server.pollname);
	dump_list(ctl->oldsaved);
	report_complete(stdout, "\n");
    }

    if (ctl->newsaved)
    {

	if (outlevel >= O_DEBUG)
	    report(stdout, GT_("discarding new UID list\n"));
	free_str_list(&ctl->newsaved);
	ctl->newsaved = (struct idlist *) NULL;
    }
}
