gvrender_end_graph(GVJ_t * job)
{
    gvrender_engine_t *gvre = job->render.engine;

    if (gvre) {
	if (gvre->end_graph)
	    gvre->end_graph(job);
    }
    gvdevice_format(job);
}
