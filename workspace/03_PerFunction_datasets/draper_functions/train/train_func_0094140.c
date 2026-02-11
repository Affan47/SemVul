mailbox_user_flag(struct mailbox *mailbox, const char *flag,
		      int *flagnum)
{
    int userflag;
    int emptyflag = -1;

    for (userflag = 0; userflag < MAX_USER_FLAGS; userflag++) {
	if (mailbox->flagname[userflag]) {
	    if (!strcasecmp(flag, mailbox->flagname[userflag]))
		break;
	}
	else if (emptyflag == -1) {
	    emptyflag = userflag;
	}
    }

    if (userflag == MAX_USER_FLAGS) {
	if (emptyflag == -1)
	    return IMAP_USERFLAG_EXHAUSTED;


	if (!mailbox_index_islocked(mailbox, 1))
	    return IMAP_MAILBOX_LOCKED;


	userflag = emptyflag;
	mailbox->flagname[userflag] = xstrdup(flag);
	mailbox->header_dirty = 1;
    }

    *flagnum = userflag;

    return 0;
}
