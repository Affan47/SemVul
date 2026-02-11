granite(float s, float t, float Kd,GLdouble Col[])
{
	float sum = 0;
	float freq = 1.0;
	int i;
	for (i = 0 ; i < 6 ; i++ )
	{
		sum += fabs(.5 - noise(12*freq*s,12*freq*t))/freq*1.4 ;
		freq *= 2;
	}
        if ( sum > 1/Kd )
		sum = 1/Kd ;
	Col[0] = sum * Kd ;
	Col[1] = sum * Kd ;
	Col[2] = sum * Kd ;
}
