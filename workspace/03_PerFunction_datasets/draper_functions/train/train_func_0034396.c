gvdevice_format(GVJ_t * job)
{
    gvdevice_engine_t *gvde = job->device.engine;

    if (gvde && gvde->format)
	gvde->format(job);
    gvflush (job);
}
