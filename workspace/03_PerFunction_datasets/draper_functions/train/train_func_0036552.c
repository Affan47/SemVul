try_pvc(const char *text,struct sockaddr_atmpvc *addr,int flags)
{
    int part[3];
    int i;

    part[0] = part[1] = part[2] = 0;
    i = 0;
    while (1) {
	if (!*text) return FATAL;
	if (i == 3) return TRY_OTHER;
	if (isdigit(*text)) {
	    if (*text == '0' && isdigit(text[1])) return TRY_OTHER;

	    do {
		if (part[i] > INT_MAX/10) return TRY_OTHER;
		part[i] = part[i]*10+*text++-'0';
	    }
	    while (isdigit(*text));
	    i++;
	    if (!*text) break;
	    if (*text++ != '.') return TRY_OTHER;
	    continue;
	}
	if (*text == '*') {
	    if (!(flags & T2A_WILDCARD)) return FATAL;
	    part[i++] = ATM_ITF_ANY;
	}
	else {
	    if (*text != '?') return TRY_OTHER;
	    if (!(flags & T2A_UNSPEC)) return FATAL;
	    part[i++] = ATM_VPI_UNSPEC;

	}
	if (!*++text) break;
	if (*text++ != '.') return FATAL;
    }
    if (i < 2) return TRY_OTHER;
    if (i == 2) {
	part[2] = part[1];
	part[1] = part[0];
	part[0] = 0;
    }
    if (part[0] > SHRT_MAX || part[2] > ATM_MAX_VCI)
	return TRY_OTHER;
    if (part[1] > (flags & T2A_NNI ? ATM_MAX_VPI_NNI : ATM_MAX_VPI))
	return TRY_OTHER;
    if (part[0] == ATM_VPI_UNSPEC) return FATAL;
    addr->sap_family = AF_ATMPVC;
    addr->sap_addr.itf = part[0];
    addr->sap_addr.vpi = part[1];
    addr->sap_addr.vci = part[2];
    return 0;
}
