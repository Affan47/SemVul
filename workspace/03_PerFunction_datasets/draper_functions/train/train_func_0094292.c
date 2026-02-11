DXGetCameraResolution(Camera c, int *width, int *height)
{
    CHECK(c, CLASS_CAMERA);

    if (width)
	*width = c->resolution;
    if (height)
	*height = c->resolution*c->aspect;

    return c;
}
