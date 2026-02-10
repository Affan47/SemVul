ulong_to_longchs(unsigned long sno, struct geometry G) {
    longchs aa;

    if (G.heads && G.sectors && G.cylindersize) {
	aa.s = 1 + sno % G.sectors;
	aa.h = (sno / G.sectors) % G.heads;
	aa.c = sno / G.cylindersize;
	return aa;
    } else {
	return zero_longchs;
    }
}
