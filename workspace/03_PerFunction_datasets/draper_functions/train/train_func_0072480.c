computeAABB()
{
	aabb[0] = -dInfinity;
	aabb[1] = dInfinity;
	aabb[2] = -dInfinity;
	aabb[3] = dInfinity;
	aabb[4] = -dInfinity;
	aabb[5] = dInfinity;


	if ( p[1] == 0.0f && p[2] == 0.0f ) {

		aabb[0] = (p[0] > 0) ? -dInfinity : -p[3];
		aabb[1] = (p[0] > 0) ? p[3] : dInfinity;
	} else
	if ( p[0] == 0.0f && p[2] == 0.0f ) {

		aabb[2] = (p[1] > 0) ? -dInfinity : -p[3];
		aabb[3] = (p[1] > 0) ? p[3] : dInfinity;
	} else
	if ( p[0] == 0.0f && p[1] == 0.0f ) {

		aabb[4] = (p[2] > 0) ? -dInfinity : -p[3];
		aabb[5] = (p[2] > 0) ? p[3] : dInfinity;
	}
}
