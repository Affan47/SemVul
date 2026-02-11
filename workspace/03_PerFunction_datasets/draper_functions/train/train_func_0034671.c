MaskSeq(long start, long end, e_type E)

{
	long	i;
	char	*s;

	if(start < 1 || start > end || end > (long) LenSeq(E)){
		seq_error("MaskSeq( ) - out of range.");
	}
	if(E->xnu) s = E->X;
	else s = E->S;
	for(i=start; i <= end; i++) s[i] = 0;
}
