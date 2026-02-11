notify_zephyr(const char *class, const char *priority,
		    const char *user, const char *mailbox,
		    int nopt, char **options,
		    const char *message)
{
    ZNotice_t notice;
    int retval;
    char myhost[256],mysender[BUFSIZ];
    char *msgbody;
    char *lines[2];
    char *mykrbhost = 0;

    if (!*user) return strdup("NO zephyr recipient not specified");

    if ((retval = ZInitialize()) != ZERR_NONE) {
	syslog(LOG_ERR, "IOERROR: cannot initialize zephyr: %m");
	return strdup("NO cannot initialize zephyr");
    }

    if (gethostname(myhost,sizeof(myhost)) == -1) {
	syslog(LOG_ERR, "IOERROR: cannot get hostname: %m");
	return strdup("NO zephyr cannot get hostname");
    }
    myhost[sizeof(myhost)-1] = '\0';

#ifdef HAVE_KRB
    mykrbhost = krb_get_phost(myhost);
#endif

    lines[0] = myhost;
    msgbody = xmalloc(1000 + strlen(message));
    lines[1] = msgbody;

    strcpy(msgbody,"");

    if (*mailbox) {
	snprintf(msgbody,900, "You have new mail in %s.\n\n", mailbox);
    }

    if (*message) {
	strcat(msgbody, message);
	strcat(msgbody, "\n");
    }

    (void) snprintf(mysender, sizeof(mysender), "imap%s%s@%s",
		   mykrbhost ? "." : "",
		   mykrbhost ? mykrbhost : "",
		   ZGetRealm());

    memset((char *)&notice, 0, sizeof(notice));
    notice.z_kind = UNSAFE;
    notice.z_class = *class ? (char *) class : MAIL_CLASS;
    notice.z_class_inst = *priority ? (char *) priority :
	*mailbox ? (char *) mailbox : "INBOX";

    notice.z_opcode = "";
    notice.z_sender = mysender;
    notice.z_default_format = "From Post Office $1:\n$2";

    notice.z_recipient = (char *) user;

    retval = ZSendList(&notice,lines,2,ZNOAUTH);


    while (retval == ZERR_NONE && nopt) {
	notice.z_recipient = (char *) options[--nopt];

	retval = ZSendList(&notice,lines,2,ZNOAUTH);
    }

    free(msgbody);

    if (retval != ZERR_NONE) {
	syslog(LOG_ERR, "IOERROR: cannot send zephyr notice: %m");
	return strdup("NO cannot send zephyr notice");
    }

    return strdup("OK zephyr notification successful");
}
