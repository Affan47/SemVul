gf_plane_intersect_line(GF_Plane *plane, GF_Vec *linepoint, GF_Vec *linevec, GF_Vec *outPoint)
{
	Fixed t, t2;
	t2 = gf_vec_dot(plane->normal, *linevec);
	if (t2 == 0) return 0;
	t = - gf_divfix((gf_vec_dot(plane->normal, *linepoint) + plane->d) , t2);
	if (t<0) return 0;
	*outPoint = gf_vec_scale(*linevec, t);
	gf_vec_add(*outPoint, *linepoint, *outPoint);
	return 1;
}
