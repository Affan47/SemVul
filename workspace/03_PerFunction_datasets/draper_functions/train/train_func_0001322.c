CCtrace(av)
    char	*av[];
{
    char	*p;
    BOOL	Flag;
    STRING	word;
    CHANNEL	*cp;


    p = av[1];
    switch (p[0]) {
    default:			return "1 Bad trace flag";
    case 'y': case 'Y':		Flag = TRUE;	word = "on";	break;
    case 'n': case 'N':		Flag = FALSE;	word = "off";	break;
    }


    p = av[0];
    switch (*p) {
    default:
	return "1 Bad trace item";
    case 'i': case 'I':
	Tracing = Flag;
	syslog(L_NOTICE, "%s trace innd %s", LogName, word);
	break;
    case 'n': case 'N':
	NNRPTracing = Flag;
	syslog(L_NOTICE, "%s trace nnrpd %s", LogName, word);
	break;
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
	if ((cp = CHANfromdescriptor(atoi(p))) == NULL)
	    return CCnochannel;
	CHANtracing(cp, Flag);
	break;
    }
    return NULL;
}
