RCcanpost(cp, group)
    register CHANNEL	*cp;
    register char	*group;
{
    register REMOTEHOST	*rp;
    register char	match;
    register char	subvalue;
    register char	**argv;
    register char	*pat;
    register int	i;

    for (rp = RCpeerlist, i = RCnpeerlist; --i >= 0; rp++) {

	if (cp->Address.s_addr != rp->Address.s_addr)
	    continue;
	if (rp->Patterns == NULL)
	    break;
	for (match = 0, argv = rp->Patterns; (pat = *argv++) != NULL; ) {
	    subvalue = (*pat != SUB_NEGATE) && (*pat != SUB_POISON) ?
	      0 : *pat;
	    if (subvalue)
		pat++;
	    if ((match != subvalue) && wildmat(group, pat)) {
		if (subvalue == SUB_POISON)
		    return -1;
		match = subvalue;
	    }
	}
	return !match;
    }
    return 1;
}
