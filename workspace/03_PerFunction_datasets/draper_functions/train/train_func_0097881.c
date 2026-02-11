getNextAction()
{
	vector< AlphaReal > cumsum( getArmNumber()+1 );
	int i;

	cumsum[0] = 0.0;
	for( int i=0; i < getArmNumber(); i++ )
	{
		cumsum[i+1] = cumsum[i] + _p[i];
	}

	for( i=0; i < getArmNumber(); i++ )
	{
		cumsum[i+1] /= cumsum[  getArmNumber() ];
	}

	AlphaReal r = rand() / (AlphaReal) RAND_MAX;

	for( i=0; i < getArmNumber(); i++ )
	{
		if ( (cumsum[i] <= r) && ( r<=cumsum[i+1] )  ) break;
	}

	return i;
}
