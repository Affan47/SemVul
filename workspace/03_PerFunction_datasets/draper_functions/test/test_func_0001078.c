map_label(GVJ_t *job, textlabel_t *lab)
{
    obj_state_t *obj = job->obj;
    int flags = job->flags;
    pointf *p;

    if (flags & (GVRENDER_DOES_MAPS | GVRENDER_DOES_TOOLTIPS)) {
	if (flags & GVRENDER_DOES_MAP_RECTANGLE) {
	    obj->url_map_shape = MAP_RECTANGLE;
	    obj->url_map_n = 2;
	}
	else {
	    obj->url_map_shape = MAP_POLYGON;
	    obj->url_map_n = 4;
	}
	free(obj->url_map_p);
	obj->url_map_p = p = N_NEW(obj->url_map_n, pointf);
	P2RECT(lab->pos, p, lab->dimen.x / 2., lab->dimen.y / 2.);
	if (! (flags & GVRENDER_DOES_TRANSFORM))
	    gvrender_ptf_A(job, p, p, 2);
	if (! (flags & GVRENDER_DOES_MAP_RECTANGLE))
	    rect2poly(p);
    }
}
