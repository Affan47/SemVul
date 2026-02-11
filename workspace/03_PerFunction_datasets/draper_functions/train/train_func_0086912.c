InitRandArray( unsigned char * a, int len )
{
	int i;


	if ( !a || (len <= 0) )
	{
		return;
	}

	if ( RAND_bytes(a,len) != 1 )
	{
		srand(time(NULL));

		for(i=0;i<len;i++)
			a[i]=(unsigned char)(rand()&0xff);
	}
}
