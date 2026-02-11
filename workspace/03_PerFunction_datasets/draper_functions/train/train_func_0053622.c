ReadHSCX(struct IsdnCardState *cs, int hscx, u_char offset)
{
	u_short off2 = offset;

	switch (cs->subtyp) {
	case R647:
		off2 = ((off2 << 8 & 0xf000) | (off2 & 0xf));
	case R685:
		return (readreg(cs->hw.gazel.hscx[hscx], off2));
	case R753:
	case R742:
		return (readreg_ipac(cs->hw.gazel.ipac, hscx * 0x40 + off2));
	}
	return 0;
}
