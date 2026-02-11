run_test(bool optimized GCC_UNUSED)
{
    char ch;
    int lo = continuous ? LO_CHAR : 'a' - LINES;
    int hi = continuous ? HI_CHAR : 'a' + LINES;

    if (lo < LO_CHAR)
	lo = LO_CHAR;
    if (hi > HI_CHAR)
	hi = HI_CHAR;

#if defined(TRACE) || defined(NCURSES_TEST)
    if (optimized) {
	Trace(("With hash mapping"));
	_nc_optimize_enable |= OPTIMIZE_HASHMAP;
    } else {
	Trace(("Without hash mapping"));
	_nc_optimize_enable &= ~OPTIMIZE_HASHMAP;
    }
#endif

    if (reverse_loops)
	for (ch = hi; ch >= lo; ch--)
	    one_cycle(ch);
    else
	for (ch = lo; ch <= hi; ch++)
	    one_cycle(ch);
}
