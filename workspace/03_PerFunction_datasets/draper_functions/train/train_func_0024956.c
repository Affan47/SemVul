mkspacep(int size)
{
    if (size > maxpn) {
	int newmax = maxpn + (size / PINC + 1) * PINC;
	ps = RALLOC(newmax, ps, pointf);
	if (!ps) {
	    agerr(AGERR, "cannot re-allocate ps\n");
	    return 1;
	}
	maxpn = newmax;
    }
    return 0;
}
