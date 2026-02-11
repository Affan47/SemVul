gvrender_set_gradient_vals (GVJ_t * job, char *stopcolor, int angle, float frac)
{
    gvrender_engine_t *gvre = job->render.engine;
    gvcolor_t *color = &(job->obj->stopcolor);

    if (gvre) {
	gvrender_resolve_color(job->render.features, stopcolor, color);
	if (gvre->resolve_color)
	    gvre->resolve_color(job, color);
    }
    job->obj->gradient_angle = angle;
    job->obj->gradient_frac = frac;
}
