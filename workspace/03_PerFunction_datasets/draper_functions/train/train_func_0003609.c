complexSD(unsigned int length, double *srcMagnitude, double *srcPhase)
{
    unsigned int i;
    double val = 0;
    double tmpPhase = 0;
    double tmpReal = 0;
    double tmpImag = 0;

    double dev = 0;
    ComplexData meas = ComplexData( 0, 0 );
    ComplexData j = ComplexData( 0, 1 );

    for( i = 0; i < length; i++)
    {
	tmpPhase = (srcPhase[ i ]- 2*m_phaseHistory[ i ]+m_phaseHistoryOld[ i ]);
	dev= MathUtilities::princarg( tmpPhase );

	meas = m_magHistory[i] - ( srcMagnitude[ i ] * exp( j * dev) );

	tmpReal = real( meas );
	tmpImag = imag( meas );

	val += sqrt( (tmpReal * tmpReal) + (tmpImag * tmpImag) );

	m_phaseHistoryOld[ i ] = m_phaseHistory[ i ] ;
	m_phaseHistory[ i ] = srcPhase[ i ];
	m_magHistory[ i ] = srcMagnitude[ i ];
    }

    return val;
}
