YM2203Read(int n,int a)
{
	YM2203 *F2203 = &(FM2203[n]);
	int addr = F2203->OPN.ST.address;
	UINT8 ret = 0;

	if( !(a&1) )
	{
		ret = FM_STATUS_FLAG(&F2203->OPN.ST);
	}
	else
	{
		if( addr < 16 ) ret = SSGRead(n);
	}
	return ret;
}
