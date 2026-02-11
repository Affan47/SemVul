release_ioregs(struct IsdnCardState *cs, int mask)
{
	if (mask & 1)
		release_region(cs->hw.teles3.isac + 32, 32);
	if (mask & 2)
		release_region(cs->hw.teles3.hscx[0] + 32, 32);
	if (mask & 4)
		release_region(cs->hw.teles3.hscx[1] + 32, 32);
}
