R_SetFrustum (void)
{
	int		i;


	RotatePointAroundVector( frustum[0].normal, vup, vpn, -(90-r_newrefdef.fov_x / 2 ) );

	RotatePointAroundVector( frustum[1].normal, vup, vpn, 90-r_newrefdef.fov_x / 2 );

	RotatePointAroundVector( frustum[2].normal, vright, vpn, 90-r_newrefdef.fov_y / 2 );

	RotatePointAroundVector( frustum[3].normal, vright, vpn, -( 90 - r_newrefdef.fov_y / 2 ) );

	for (i=0 ; i<4 ; i++)
	{
		frustum[i].type = PLANE_ANYZ;
		frustum[i].dist = DotProduct (r_origin, frustum[i].normal);
		frustum[i].signbits = SignbitsForPlane (&frustum[i]);
	}
}
