CHANclose(CHANNEL *cp, const char *name)
{
    int i;

    if (cp->Type == CTfree)
        warn("%s internal closing free channel %d", name, cp->fd);
    else {
        if (cp->Type == CTnntp)
            CHANclose_nntp(cp, name);
        else if (cp->Type == CTreject)
            notice("%s %ld", name, cp->Rejected);
        else if (cp->Out.left)
            warn("%s closed lost %lu", name, (unsigned long) cp->Out.left);
        else
            notice("%s closed", name);
        WCHANremove(cp);
        RCHANremove(cp);
        SCHANremove(cp);
        if (cp->fd >= 0 && close(cp->fd) < 0)
            syswarn("%s cant close %s", LogName, name);
        for (i = 0; i < channels.prioritized_size; i++)
            if (channels.prioritized[i] == cp)
                channels.prioritized[i] = NULL;
    }


    cp->Type = CTfree;
    cp->State = CSerror;
    cp->fd = -1;
    if (cp->Argument != NULL)
        free(cp->Argument);
    cp->Argument = NULL;
    cp->ActiveCnx = 0;


    if (cp->In.size > BIG_BUFFER) {
        cp->In.size = 0;
        cp->In.used = 0;
        cp->In.left = 0;
        free(cp->In.data);
        cp->In.data = NULL;
    }
    if (cp->Out.size > BIG_BUFFER) {
        cp->Out.size = 0;
        cp->Out.used = 0;
        cp->Out.left = 0;
        free(cp->Out.data);
        cp->Out.data = NULL;
    }


    if (cp->Sendid.size > 0) {
        cp->Sendid.size = 0;
        cp->Sendid.used = 0;
        cp->Sendid.left = 0;
        free(cp->Sendid.data);
        cp->Sendid.data = NULL;
    }


    if (cp->av != NULL) {
        free(cp->av[0]);
        free(cp->av);
        cp->av = NULL;
    }
}
