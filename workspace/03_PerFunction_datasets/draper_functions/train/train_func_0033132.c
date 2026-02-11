RotateSetCamera(void *data, float to[3], float from[3], float up[3],
		    int proj, float fov, float width)
{
    int i;
    RotateData rdata = (RotateData)data;


    for (i = 0; i < 3; i++)
	rdata->to[i]   = to[i],
	rdata->from[i] = from[i],
	rdata->up[i]   = up[i];

    rdata->p     = proj;
    rdata->fov   = fov;
    rdata->width = width;
}
