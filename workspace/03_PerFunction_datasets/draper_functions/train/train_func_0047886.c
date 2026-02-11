_dxfCaptureDelayedColorImage(struct window *w, translationT *t, Visual *v)
{
    Field image = DXMakeImageFormat(w->wwidth, w->wheight, "DELAYEDCOLOR");
    if (image)
    {
	int    i, pixsize = _dxf_GetXBytesPerPixel(t);
	XColor xmap[256];
	float  *dxmap;
	Array  c = (Array)DXGetComponentValue(image, "colors");
	Array  m = (Array)DXGetComponentValue(image, "color map");
	if (! c || ! m)
	    goto error;

	if (pixsize == 1)
	{
	    int    y, dst_rowsize = w->wwidth, src_rowsize = pixsize*w->wwidth;
	    ubyte  *src = (ubyte *)w->pixels;
	    ubyte  *dst = ((ubyte *)DXGetArrayData(c)) +
				(w->wheight-1)*dst_rowsize;

	    for (y = 0; y < w->wheight; y++)
	    {
		memcpy(dst, src, w->wwidth);
		dst -= dst_rowsize;
		src += src_rowsize;
	    }
	}
	else
	{
	    int    y, dst_rowsize = w->wwidth;
	    ubyte  *src = (ubyte *)w->pixels;
	    ubyte  *dst = ((ubyte *)DXGetArrayData(c)) +
				(w->wheight-1)*dst_rowsize;

	    for (y = 0; y < w->wheight; y++)
	    {
		ubyte *d = dst;
		ubyte *e = d + dst_rowsize;

		while (d < e)
		{
		    *d++ = *src;
		    src += pixsize;
		}

		dst -= dst_rowsize;
	    }
	}

	for (i = 0; i < v->map_entries; i++)
	{
	    xmap[i].pixel = i;
	    xmap[i].flags = DoRed | DoGreen | DoBlue;
	}

	XQueryColors(w->dpy, (Colormap)t->cmap, xmap, v->map_entries);
	dxmap = (float *)DXGetArrayData(m);

	for (i = 0; i < v->map_entries; i++)
	{
	    *dxmap++ = xmap[i].red / 65536.0;
	    *dxmap++ = xmap[i].green / 65536.0;
	    *dxmap++ = xmap[i].blue / 65536.0;
	}

	for ( ; i < 256; i++)
	{
	    *dxmap++ = 0.0;
	    *dxmap++ = 0.0;
	    *dxmap++ = 0.0;
	}
    }

    return image;

error:
    DXDelete((Object)image);
    return ERROR;
}
