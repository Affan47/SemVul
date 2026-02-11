PerpendicularVector( vec3_t dst, const vec3_t src )
{
	int i, pos = 0;
	float minelem = 1.0F;
	vec3_t tempvec = {0, 0, 0};


	for ( i = 0; i < 3; i++ )
	{
		if ( fabs( src[i] ) < minelem )
		{
			pos = i;
			minelem = fabs( src[i] );
		}
	}
	tempvec[pos] = 1.0F;


	ProjectPointOnPlane( dst, tempvec, src );


	VectorNormalize( dst );
}
