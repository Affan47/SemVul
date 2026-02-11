YM2610Read(int n,int a)
{
	YM2610 *F2610 = &(FM2610[n]);
	int addr = F2610->OPN.ST.address;
	UINT8 ret = 0;

	switch( a&3){
	case 0:
		ret = FM_STATUS_FLAG(&F2610->OPN.ST) & 0x83;
		break;
	case 1:
		if( addr < 16 ) ret = SSGRead(n);
		if( addr == 0xff ) ret = 0x01;
		break;
	case 2:


		ret = F2610->adpcm_arrivedEndAddress;
		break;
	case 3:
		ret = 0;
		break;
	}
	return ret;
}
