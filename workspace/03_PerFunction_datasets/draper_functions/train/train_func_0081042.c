ashl(void)
{
	UINT32 src2 = SRC2VAL;
	DSTVAL = (src2 < 32) ? (SRC1VAL << src2) : 0;
}
