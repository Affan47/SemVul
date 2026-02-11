MAPfree()
{
    register PAIR	*mp;

    for (mp = MAPdata; mp < MAPend; mp++) {
	DISPOSE(mp->Key);
	DISPOSE(mp->Value);
    }
    DISPOSE(MAPdata);
    MAPdata = NULL;
}
