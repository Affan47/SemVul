InsertBlock(char *name, VPoint * o, VPoint * scale, VPoint * extrude, double r,
			VPolygon **poly, int *ptop)
{
    VObject **p;
    int i, j, extrusion = 0;

    PDEBUG(("looking for \"%s\"; offset %g, %g, %g; scale %g, %g, %g; extrude %g, %g, %g; rotate %g\n", name,
		o->x, o->y, o->z, scale->x, scale->y, scale->z,
		extrude->x, extrude->y, extrude->z, r));

    for (p = bobject, i = 0; i < btop; ++i, ++p) {
		if (strcmp((*p)->name, name) == 0) {


#ifdef notdef
			if (extrude->x != 0.0 || extrude->y != 0.0 || extrude->z != 0.0) {
				PDEBUG(("extrusion (%f, %f, %f)\n", extrude->x,
					extrude->y, extrude->z));
				extrusion = 1;
				ex_tmp = VExtrudeObject(*p, extrude);
				p = &ex_tmp;
			}
#endif


			PDEBUG(("adding %d polygons to %d existing\n",
				(*p)->numPolys, (*ptop)));
			for (j = 0; j < (*p)->numPolys; ++j) {
				poly[(*ptop)++] = ScalePolygon((*p)->polygon[j], o, scale, extrude, r);
			}


			if (extrusion) {
				for (j = 0; j < (*p)->numPolys; ++j) {
					VDestroyPolygon((*p)->polygon[j]);
					free((char *) (*p));
				}
			}

			return;
		}
    }
}
