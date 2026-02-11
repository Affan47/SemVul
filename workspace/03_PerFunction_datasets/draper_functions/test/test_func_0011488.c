ModifyRangeMultiplier(char *range, int mult)
{
	RangeType *rp = FindRange(range);
	if (rp == NULL) return;
	if(mult < 1) return;
	rp->rangeMult = mult;
}
