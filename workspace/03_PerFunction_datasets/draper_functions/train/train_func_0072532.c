PerlinNoise_2D(float x, float y)
{
	float total = 0 ;
	float p = 0.25 ;
	int n = 3 ;
	float frequency;
	float amplitude;
	int i;

	for (i = 0 ; i <= n ; i++ )
	{
		frequency = 2<<i ;
		amplitude = pow(p,i) ;
		total += InterpolatedNoise_1(x * frequency,y*frequency) * amplitude ;
	}
	return (total) ;
}
