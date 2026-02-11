fill_polygon(PLStream *pls)
{
png_Dev *dev=(png_Dev *)pls->dev;

    int i;
    gdPoint *points=NULL;

    if (pls->dev_npts < 1)
	return;

     points = malloc((size_t)pls->dev_npts * sizeof(gdPoint));

     for (i = 0; i < pls->dev_npts; i++)
         {
	   points[i].x = pls->dev_x[i]/dev->scale;
	   points[i].y = dev->pngy - (pls->dev_y[i]/dev->scale);
         }

    #if GD2_VERS >= 2
      if (dev->smooth==1)
        {
          gdImageSetAntiAliased(dev->im_out,dev->colour);
          gdImageFilledPolygon(dev->im_out, points, pls->dev_npts, gdAntiAliased);
        }
      else
        {
          gdImageFilledPolygon(dev->im_out, points, pls->dev_npts, dev->colour);
        }
    #else
      gdImageFilledPolygon(dev->im_out, points, pls->dev_npts, dev->colour);
    #endif

   free(points);

}
