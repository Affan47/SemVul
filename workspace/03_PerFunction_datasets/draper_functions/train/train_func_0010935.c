release_sink(struct query *ctl)

{
    if (ctl->bsmtp && sinkfp)
    {
	if (strcmp(ctl->bsmtp, "-"))
	{
	    fclose(sinkfp);
	    sinkfp = (FILE *)NULL;
	}
    }
    else if (ctl->mda)
    {
	if (sinkfp)
	{
	    pclose(sinkfp);
	    sinkfp = (FILE *)NULL;
	}
	deal_with_sigchld();
    }
}
