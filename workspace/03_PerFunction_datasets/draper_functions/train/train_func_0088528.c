lwpoint_get_ordinate(const POINT4D *p, int ordinate)
{
	if ( ! p )
	{
		lwerror("Null input geometry.");
		return 0.0;
	}

	if ( ordinate > 3 || ordinate < 0 )
	{
		lwerror("Cannot extract ordinate %d.", ordinate);
		return 0.0;
	}

	if ( ordinate == 3 )
		return p->m;
	if ( ordinate == 2 )
		return p->z;
	if ( ordinate == 1 )
		return p->y;

	return p->x;

}
