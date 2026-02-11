CheckControl(char *ctrl)
{
    char	*p;
    char	*q;
    char		save;


    for (p = ctrl; ISWHITE(*p); p++)
	continue;
    for (ctrl = p; *p && !ISWHITE(*p); p++)
	continue;
    if (p == ctrl)
        die("emtpy control message");
    save = *p;
    *p = '\0';

    if (strcasecmp(ctrl, "cancel") == 0) {
	for (q = p + 1; ISWHITE(*q); q++)
	    continue;
	if (*q == '\0')
            die("message ID missing in cancel");
	if (!Spooling)
	    CheckCancel(q, false);
    }
    else if (strcasecmp(ctrl, "checkgroups") == 0
	  || strcasecmp(ctrl, "ihave")       == 0
	  || strcasecmp(ctrl, "sendme")      == 0
	  || strcasecmp(ctrl, "newgroup")    == 0
	  || strcasecmp(ctrl, "rmgroup")     == 0
	  || strcasecmp(ctrl, "sendsys")     == 0
	  || strcasecmp(ctrl, "senduuname")  == 0
	  || strcasecmp(ctrl, "version")     == 0) {
	if (!AnAdministrator())
            die("ask your news administrator to do the %s for you", ctrl);
    }
    else {
        die("%s is not a valid control message", ctrl);
    }
    *p = save;
}
