CheckControl(ctrl)
    char	*ctrl;
{
    register char	*p;
    register char	*q;
    char		save;


    for (p = ctrl; ISWHITE(*p); p++)
	continue;
    for (ctrl = p; *p && !ISWHITE(*p); p++)
	continue;
    if (p == ctrl)
	return "Empty control message";
    save = *p;
    *p = '\0';

    if (EQ(ctrl, "cancel")) {
	for (q = p + 1; ISWHITE(*q); q++)
	    continue;
	if (*q == '\0')
	    return "Message-ID missing in cancel";
    }
    else if (EQ(ctrl, "sendsys") || EQ(ctrl, "senduuname")
	  || EQ(ctrl, "version") || EQ(ctrl, "checkgroups")
	  || EQ(ctrl, "ihave") || EQ(ctrl, "sendme")
	  || EQ(ctrl, "newgroup") || EQ(ctrl, "rmgroup"))

	;
    else {
	(void)sprintf(Error, "\"%s\" is not a valid control message",
		MaxLength(ctrl,ctrl));
	return Error;
    }
    *p = save;
    return NULL;
}
