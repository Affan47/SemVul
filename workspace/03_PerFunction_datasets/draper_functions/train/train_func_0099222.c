timesub(GTimeVal end, GTimeVal start) {
    GTimeVal diff;

    if(end.tv_usec < start.tv_usec) {
	if (end.tv_sec > 0)
	    end.tv_sec -= 1;
	end.tv_usec += 1000000;
    }
    diff.tv_usec = end.tv_usec - start.tv_usec;

    if (end.tv_sec > start.tv_sec)
	diff.tv_sec = end.tv_sec - start.tv_sec;
    else
	diff.tv_sec = 0;

    return diff;
}
