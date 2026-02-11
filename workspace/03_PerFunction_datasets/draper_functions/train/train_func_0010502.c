GetMultiplicity2Evector( Sym3x3 const& matrix, float evalue )
{

	Sym3x3 m;
	m[0] = matrix[0] - evalue;
	m[1] = matrix[1];
	m[2] = matrix[2];
	m[3] = matrix[3] - evalue;
	m[4] = matrix[4];
	m[5] = matrix[5] - evalue;


	float mc = std::fabs( m[0] );
	int mi = 0;
	for( int i = 1; i < 6; ++i )
	{
		float c = std::fabs( m[i] );
		if( c > mc )
		{
			mc = c;
			mi = i;
		}
	}


	switch( mi )
	{
	case 0:
	case 1:
		return Vec3( -m[1], m[0], 0.0f );

	case 2:
		return Vec3( m[2], 0.0f, -m[0] );

	case 3:
	case 4:
		return Vec3( 0.0f, -m[4], m[3] );

	default:
		return Vec3( 0.0f, -m[5], m[4] );
	}
}
