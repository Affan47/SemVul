gvrender_begin_layer(GVJ_t * job)
{
    gvrender_engine_t *gvre = job->render.engine;

    if (gvre) {
	if (gvre->begin_layer)
	    gvre->begin_layer(job, job->gvc->layerIDs[job->layerNum],
			      job->layerNum, job->numLayers);
    }
}
