xlist_flags(const char *mboxname, char *sep)
{
    char inboxname[MAX_MAILBOX_PATH+1];
    int inboxlen;

    (*imapd_namespace.mboxname_tointernal)(&imapd_namespace, "INBOX",
					   imapd_userid, inboxname);
    inboxlen = strlen(inboxname);


    if (strncmp(mboxname, inboxname, inboxlen))
	return;


    if (mboxname[inboxlen] == '\0') {
	prot_printf(imapd_out, "%s\\Inbox", sep);
    }

    else if (mboxname[inboxlen] == '.') {
	struct xlist_rock rock;
	rock.sep = sep;
	rock.mboxname = mboxname + inboxlen + 1;
	config_foreachoverflowstring(xlist_check, &rock);
    }


}
