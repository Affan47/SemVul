open_sink(struct query *ctl, struct msgblk *msg,
	      int *good_addresses, int *bad_addresses)

{
    *bad_addresses = *good_addresses = 0;

    if (want_progress() && outlevel >= O_VERBOSE && !ctl->mda && !ctl->bsmtp) puts("");

    if (ctl->bsmtp)
	return(open_bsmtp_sink(ctl, msg, good_addresses, bad_addresses));


    else if (!ctl->mda && smtp_setup(ctl) != -1)
	return(open_smtp_sink(ctl, msg, good_addresses, bad_addresses));


    else if (!ctl->mda)
    {
	report(stderr, GT_("%cMTP connect to %s failed\n"),
	       ctl->smtphostmode,
	       ctl->smtphost ? ctl->smtphost : "localhost");

#ifndef FALLBACK_MDA

	return(PS_SMTP);
#else


	if (ctl->smtphost && strcmp(ctl->smtphost, "localhost"))
	    return(PS_SMTP);


	ctl->mda = FALLBACK_MDA;
	if (!ctl->forcecr)
	    ctl->stripcr = TRUE;

	report(stderr, GT_("can't raise the listener; falling back to %s"),
			 FALLBACK_MDA);
#endif
    }

    if (ctl->mda)
	return(open_mda_sink(ctl, msg, good_addresses, bad_addresses));

    return(PS_SUCCESS);
}
