compute_offsets(char **Strings, unsigned strmax, short *offsets)
{
    size_t nextfree = 0;
    unsigned i;

    for (i = 0; i < strmax; i++) {
	if (Strings[i] == ABSENT_STRING) {
	    offsets[i] = -1;
	} else if (Strings[i] == CANCELLED_STRING) {
	    offsets[i] = -2;
	} else {
	    offsets[i] = nextfree;
	    nextfree += strlen(Strings[i]) + 1;
	    TRACE_OUT(("put Strings[%d]=%s(%d)", (int) i,
		       _nc_visbuf(Strings[i]), (int) nextfree));
	}
    }
    return nextfree;
}
