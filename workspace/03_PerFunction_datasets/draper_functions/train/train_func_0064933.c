putRGBseparate8bittile(
    u_long* cp,
    const u_char* r, const u_char* g, const u_char* b,
    const RGBvalue* Map,
    u_long w, u_long h,
    int fromskew, int toskew
)
{
    if (Map) {
	while (h-- > 0) {
	    u_long x;
	    for (x = w; x > 0; x--)
		*cp++ = PACK(Map[*r++], Map[*g++], Map[*b++]);
	    SKEW(r, g, b, fromskew);
	    cp += toskew;
	}
    } else {
	while (h-- > 0) {
	    UNROLL8(w,, *cp++ = PACK(*r++, *g++, *b++));
	    SKEW(r, g, b, fromskew);
	    cp += toskew;
	}
    }
}
