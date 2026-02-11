PlaneTypeForNormal (const vec3_t normal)
{
	vec_t	ax, ay, az;


	if (normal[0] >= 1.0f)
		return PLANE_X;
	if (normal[1] >= 1.0f)
		return PLANE_Y;
	if (normal[2] >= 1.0f)
		return PLANE_Z;

	ax = (float)fabs( normal[0] );
	ay = (float)fabs( normal[1] );
	az = (float)fabs( normal[2] );

	if (ax >= ay && ax >= az)
		return PLANE_ANYX;
	if (ay >= ax && ay >= az)
		return PLANE_ANYY;
	return PLANE_ANYZ;
}
