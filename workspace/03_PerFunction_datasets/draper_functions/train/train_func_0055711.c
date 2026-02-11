GollyGhostUpdateLED_c8( int data )
{
	static char time1[32];
	static char zap100[32];
	int i = 0;
	for(;;)
	{
		artwork_show(time1,i);
		artwork_show(zap100,i);
		if( i ) return;
		sprintf( time1,  "time1_%d", data>>4);
		sprintf( zap100, "zap100_%d",data&0xf);
		i=1;
	}
}
