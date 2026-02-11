getMax( double* pData, unsigned int Length, double* pMax )
{
	unsigned int index = 0;
	unsigned int i;
	double temp = 0.0;

	double max = pData[0];

	for( i = 0; i < Length; i++)
	{
		temp = pData[ i ];

		if( temp > max )
		{
			max =  temp ;
			index = i;
		}

   	}

	if (pMax) *pMax = max;


	return index;
}
