_evas_yv12torgb_raster(unsigned char **yuv, unsigned char *rgb, int w, int h)
{
#ifdef BUILD_C
   int xx, yy;
   int y, u, v;
   unsigned char *yp1, *yp2, *up, *vp;
   unsigned char *dp1, *dp2;


   dp1 = rgb;
   dp2 = rgb + (w * 4);

   for (yy = 0; yy < h; yy += 2)
     {

	yp1 = yuv[yy];
	yp2 = yuv[yy + 1];
	up = yuv[h + (yy / 2)];
	vp = yuv[h + (h / 2) + (yy / 2)];
	for (xx = 0; xx < w; xx += 2)
	  {
	     int vmu;


	     u = *up++;
	     v = *vp++;


	     vmu = _v813[v] + _v391[u];
	     u = _v2018[u];
	     v = _v1596[v];


	     y = _v1164[*yp1++];
	     *((DATA32 *) dp1) = 0xff000000 + RGB_JOIN(LUT_CLIP(y + v), LUT_CLIP(y - vmu), LUT_CLIP(y + u));

	     dp1 += 4;


	     y = _v1164[*yp1++];
	     *((DATA32 *) dp1) = 0xff000000 + RGB_JOIN(LUT_CLIP(y + v), LUT_CLIP(y - vmu), LUT_CLIP(y + u));

	     dp1 += 4;


	     y = _v1164[*yp2++];
	     *((DATA32 *) dp2) = 0xff000000 + RGB_JOIN(LUT_CLIP(y + v), LUT_CLIP(y - vmu), LUT_CLIP(y + u));

	     dp2 += 4;


	     y = _v1164[*yp2++];
	     *((DATA32 *) dp2) = 0xff000000 + RGB_JOIN(LUT_CLIP(y + v), LUT_CLIP(y - vmu), LUT_CLIP(y + u));

	     dp2 += 4;
	  }

	dp1 += (w * 4);
	dp2 += (w * 4);
     }
#endif
}
