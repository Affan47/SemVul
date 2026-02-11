send_size_warnings(struct query *ctl)

{
    int size, nbr;
    int msg_to_send = FALSE;
    struct idlist *head=NULL, *current=NULL;
    int max_warning_poll_count;

    head = ctl->skipped;
    if (!head)
	return;


    for (current = head; current; current = current->next)
	if (current->val.status.num == 0 && current->val.status.mark)
	    msg_to_send = TRUE;
    if (!msg_to_send)
	return;


    if (open_warning_by_mail(ctl))
	return;
    stuff_warning(iana_charset, ctl,
	   GT_("Subject: Fetchmail oversized-messages warning"));
    stuff_warning(NULL, ctl, "%s", "");
    if (ctl->limitflush)
	stuff_warning(NULL, ctl,
		GT_("The following oversized messages were deleted on server %s account %s:"),
		ctl->server.pollname, ctl->remotename);
    else
	stuff_warning(NULL, ctl,
		GT_("The following oversized messages remain on server %s account %s:"),
		ctl->server.pollname, ctl->remotename);

    stuff_warning(NULL, ctl, "%s", "");

    if (run.poll_interval == 0)
	max_warning_poll_count = 0;
    else
	max_warning_poll_count = ctl->warnings/run.poll_interval;


    for (current = head; current; current = current->next)
    {
	if (current->val.status.num == 0 && current->val.status.mark)
	{
	    nbr = current->val.status.mark;
	    size = atoi(current->id);
	    if (ctl->limitflush)
		stuff_warning(NULL, ctl,
			ngettext("  %d message  %d octets long deleted by fetchmail.",
			         "  %d messages %d octets long deleted by fetchmail.", nbr),
			nbr, size);
	    else
		stuff_warning(NULL, ctl,
			ngettext("  %d message  %d octets long skipped by fetchmail.",
			         "  %d messages %d octets long skipped by fetchmail.", nbr),
			nbr, size);
	}
	current->val.status.num++;
	current->val.status.mark = 0;

	if (current->val.status.num >= max_warning_poll_count)
	    current->val.status.num = 0;
    }

    stuff_warning(NULL, ctl, "%s", "");

    close_warning_by_mail(ctl, (struct msgblk *)NULL);
}
