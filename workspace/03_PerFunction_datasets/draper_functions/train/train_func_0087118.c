g3_draw_sphere_ez(vec3d *pnt,float rad)
{
	vertex pt;
	ubyte flags;

	Assert( G3_count == 1 );

	flags = g3_rotate_vertex(&pt,pnt);

	if (flags == 0) {

		g3_project_vertex(&pt);

		if (!(pt.flags & PF_OVERFLOW))	{

			g3_draw_sphere( &pt, rad );
		}
	}

	return 0;
}
