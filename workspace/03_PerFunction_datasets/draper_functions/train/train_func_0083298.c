newLabel(d)
Label d; {
    if (d==RUNON) {
	if (nextLab>=NUM_FIXUPS) {
	    ERRMSG(0) "Compiled code too complex"
	    EEND;
	}
	return nextLab++;
    }
    return d;
}
