gvrender_set_pencolor(GVJ_t * job, char *name)
{
    gvrender_engine_t *gvre = job->render.engine;
    gvcolor_t *color = &(job->obj->pencolor);
    char *cp = NULL;

    if ((cp = strstr(name, ":")))
	*cp = '\0';
    if (gvre) {
	gvrender_resolve_color(job->render.features, name, color);
	if (gvre->resolve_color)
	    gvre->resolve_color(job, color);
    }
    if (cp)
	*cp = ':';
}
