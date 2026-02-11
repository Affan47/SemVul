putTupleType(e,fr)
Cell e;
Int  fr; {
    if (isAp(e)) {
	if (putTupleType(fun(e),fr))
	    putChr(',');
	putType(arg(e),NEVER,fr);
	return TRUE;
    }
    return FALSE;
}
