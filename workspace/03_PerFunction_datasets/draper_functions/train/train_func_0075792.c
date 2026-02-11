breakNow(s)
String s; {
    Breakpt b = findBreakpt(s);
    if ((b >= BRKMIN) && breakpt(b).enabled)
        if (breakpt(b).count){
	    breakpt(b).count--;
	    return FALSE;
	}
	else
	    return TRUE;
    else
        return FALSE;
}
