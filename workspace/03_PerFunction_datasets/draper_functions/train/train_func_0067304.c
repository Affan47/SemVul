gar_free_subdiv_data(struct gar_subdiv *gsd)
{
	int i, cnt;
	struct gpoint *gp;
	struct gpoly  *gl;

	cnt = ga_get_count(&gsd->points);
	for (i=0; i < cnt; i++) {
		gp = ga_get(&gsd->points, i);
		if  (gp)
			gar_free_point(gp);
	}
	ga_empty(&gsd->points);
	cnt = ga_get_count(&gsd->polylines);
	for (i=0; i < cnt; i++) {
		gl = ga_get(&gsd->polylines, i);
		if  (gl)
			gar_free_poly(gl);
	}
	ga_empty(&gsd->polylines);
	cnt = ga_get_count(&gsd->polygons);
	for (i=0; i < cnt; i++) {
		gl = ga_get(&gsd->polygons, i);
		if  (gl)
			gar_free_poly(gl);
	}
	ga_empty(&gsd->polygons);
	gsd->loaded = 0;
}
