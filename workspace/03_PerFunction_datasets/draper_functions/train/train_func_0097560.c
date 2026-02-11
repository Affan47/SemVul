NCauthinfo(CHANNEL *cp)
{
    char *buff = NULL;
    cp->Start = cp->Next;


    if (strcasecmp(cp->av[1], "USER") != 0
        && strcasecmp(cp->av[1], "PASS") != 0) {
        xasprintf(&buff, "%d Bad AUTHINFO param", NNTP_ERR_SYNTAX);
        NCwritereply(cp, buff);
        free(buff);
        return;
    }

    if (cp->IsAuthenticated) {

        if (cp->CanAuthenticate)
            xasprintf(&buff, "%d Authentication will fail", NNTP_ERR_ACCESS);
        else
            xasprintf(&buff, "%d Already authenticated", NNTP_ERR_ACCESS);
        NCwritereply(cp, buff);
        free(buff);
        return;
    }


    if (strcasecmp(cp->av[1], "USER") == 0) {
        cp->HasSentUsername = true;
        xasprintf(&buff, "%d Enter password", NNTP_CONT_AUTHINFO);
        NCwritereply(cp, buff);
        free(buff);
	return;
    }


    if (!RCauthorized(cp, cp->av[2])) {
        xasprintf(&buff, "%d Authentication failed", NNTP_FAIL_AUTHINFO_BAD);
    } else {
        xasprintf(&buff, "%d Authentication succeeded", NNTP_OK_AUTHINFO);
        cp->CanAuthenticate = false;
        cp->IsAuthenticated = true;
    }
    NCwritereply(cp, buff);
    free(buff);
}
