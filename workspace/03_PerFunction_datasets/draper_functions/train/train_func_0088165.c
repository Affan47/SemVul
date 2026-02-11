cam_keypoints_tracking2_convolve_vert(CamFloatImage *imgin, CamConvolutionKernel *kernel, CamFloatImage *imgout)
{
  float			*ptrcol;
  register float	*ptrout;
  register float	*ppp;
  register float	sum;
  register int		radius;
  register int		ncols;
  register int		nrows;
  register int		i, j, k;

  ptrcol = imgin->data;
  ptrout = imgout->data;
  radius = kernel->width / 2;
  ncols = imgin->ncols;
  nrows = imgin->nrows;
  for (i = 0 ; i < ncols ; i++)
    {

      for (j = 0 ; j < radius ; j++)
	{
	  *ptrout = 0.0;
	  ptrout += ncols;
	}

      for ( ; j < nrows - radius ; j++)
	{
	  ppp = ptrcol + ncols * (j - radius);
	  sum = 0.0;
	  for (k = kernel->width-1 ; k >= 0 ; k--)
	    {
	      sum += *ppp * kernel->data[k];
	      ppp += ncols;
	    }
	  *ptrout = sum;
	  ptrout += ncols;
	}

      for ( ; j < nrows ; j++)
	{
	  *ptrout = 0.0;
	  ptrout += ncols;
	}

      ptrcol++;
      ptrout -= nrows * ncols - 1;
    }
}
