handle_smtp_report(struct query *ctl, struct msgblk *msg)


{
    int smtperr = atoi(smtp_response);
    char *responses[1];

    responses[0] = xstrdup(smtp_response);

#ifdef __UNUSED__


    smtp_rset(ctl);
    if (outlevel >= O_DEBUG)
	report(stdout, GT_("Saved error is still %d\n"), smtperr);
#endif


    if (str_find(&ctl->antispam, smtperr))
    {


	if (run.spambounce)
	{
	    char rejmsg[160];
	    snprintf(rejmsg, sizeof(rejmsg),
		    "spam filter or virus scanner rejected message because:\r\n"
		    "%s\r\n", responses[0]);

	    send_bouncemail(ctl, msg, XMIT_ACCEPT,
		    rejmsg, 1, responses);
	}
	free(responses[0]);
	return(PS_REFUSED);
    }


    if (smtperr >= 400)
	report(stderr, GT_("%cMTP error: %s\n"),
	      ctl->smtphostmode,
	      responses[0]);

    switch (smtperr)
    {
    case 552:


	if (run.bouncemail)
	    send_bouncemail(ctl, msg, XMIT_ACCEPT,
			"This message was too large (SMTP error 552).\r\n",
			1, responses);
	free(responses[0]);
	return(PS_REFUSED);

    case 553:


#ifdef __DONT_FEED_THE_SPAMMERS__
	if (run.bouncemail)
	    send_bouncemail(ctl, msg, XMIT_ACCEPT,
			"Invalid address in MAIL FROM (SMTP error 553).\r\n",
			1, responses);
#endif
	free(responses[0]);
	return(PS_REFUSED);

    case 530:


	if (outlevel > O_SILENT)
		report_complete(stdout,
				GT_("SMTP server requires STARTTLS, keeping message.\n"));
	free(responses[0]);
	return(PS_TRANSIENT);

    default:

	if (smtperr >= 500 && smtperr <= 599)
	{
	    if (run.bouncemail)
		send_bouncemail(ctl, msg, XMIT_ACCEPT,
				"General SMTP/ESMTP error.\r\n",
				1, responses);
	    free(responses[0]);
	    return(PS_REFUSED);
	}


	free(responses[0]);
	return(PS_TRANSIENT);
    }
}
