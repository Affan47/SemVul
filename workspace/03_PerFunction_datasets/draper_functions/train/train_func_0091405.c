gar_get_object_dcoord(struct gmap *gm, struct gobject *o, int ndelta, struct gcoord *ret)
{
	struct gpoly *gp;
	if  (o->type == GO_POINT)
		return 0;
	gp = o->gptr;
	if (ndelta < gp->npoints) {
		*ret = gp->deltas[ndelta];
		return 1;
	}
	return 0;
}
