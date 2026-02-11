RCclose()
{
    register REMOTEHOST	*rp;
    register int	i;

    CHANclose(RCchan, CHANname(RCchan));
    RCchan = NULL;
    if (RCpeerlist) {
	for (rp = RCpeerlist, i = RCnpeerlist; --i >= 0; rp++) {
	    DISPOSE(rp->Name);
	    DISPOSE(rp->Password);
	    if (rp->Patterns)
		DISPOSE(rp->Patterns);
	}
	DISPOSE(RCpeerlist);
	RCpeerlist = NULL;
	RCnpeerlist = 0;
    }

    if (RCmaster) {
	DISPOSE(RCmaster);
	RCmaster = NULL;
	RCnmaster = 0;
    }
}
