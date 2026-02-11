longchs_to_chs(longchs aa, struct geometry G) {
    chs a;

    if (aa.h < 256 && aa.s < 64 && aa.c < 1024) {
	a.h = aa.h;
	a.s = aa.s | ((aa.c >> 2) & 0xc0);
	a.c = (aa.c & 0xff);
    } else if (G.heads && G.sectors) {
	a.h = G.heads - 1;
	a.s = G.sectors | 0xc0;
	a.c = 0xff;
    } else
	a = zero_chs;
    return a;
}
