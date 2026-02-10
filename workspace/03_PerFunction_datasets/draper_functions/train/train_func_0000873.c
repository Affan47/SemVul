swallow_to_glyph(int mnum, int loc)
{
    if (loc < S_sw_tl || S_sw_br < loc) {
	impossible("swallow_to_glyph: bad swallow location");
	loc = S_sw_br;
    }
    return ((int) (what_mon(mnum)<<3) | (loc - S_sw_tl)) + GLYPH_SWALLOW_OFF;
}
