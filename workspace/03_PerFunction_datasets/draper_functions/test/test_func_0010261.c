draw_face( vertex *v1, vertex *v2, vertex *v3 )
{
	vec3d norm;
	vertex *vertlist[3];

	vm_vec_perp(&norm,&v1->world, &v2->world, &v3->world);
	if ( vm_vec_dot(&norm, &v1->world ) >= 0.0 ) {
		vertlist[0] = v3;
		vertlist[1] = v2;
		vertlist[2] = v1;
	} else {
		vertlist[0] = v1;
		vertlist[1] = v2;
		vertlist[2] = v3;
	}

	g3_draw_poly( 3, vertlist, TMAP_FLAG_TEXTURED | TMAP_HTL_3D_UNLIT );

}
