model_collide_flatpoly(ubyte * p)
{
	int i;
	int nv;
	vec3d *points[TMAP_MAX_VERTS];
	short *verts;

	nv = w(p+36);
	if ( nv < 0 ) return;

	if ( nv > TMAP_MAX_VERTS ) {
		Int3();
		return;
	}

	verts = (short *)(p+44);

	for (i=0;i<nv;i++)	{
		points[i] = Mc_point_list[verts[i*2]];
	}

	if ( Mc->flags & MC_CHECK_SPHERELINE )	{
		mc_check_sphereline_face(nv, points, vp(p+20), fl(p+32), vp(p+8), NULL, -1, p, NULL);
	} else {
		mc_check_face(nv, points, vp(p+20), fl(p+32), vp(p+8), NULL, -1, p, NULL);
	}
}
