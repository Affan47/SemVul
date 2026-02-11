clip_line(n,x,y)
int *n;
double *x, *y;
{
  double xx, yy,
         px, py;

  int i,c,c1,c2;

  px = x[0];
  py = y[0];
  clip_code(px,py,&c1);
  for(i = 1; i < *n; i++)
  {
    clip_code(x[i],y[i],&c2);
    if (c1 || c2)
    {
      while(c1 || c2)
      {
        if (c1 & c2)
        {
          *n = i;
          return *n;
        }

        c = c1 ? c1 : c2;

        if (c & LEFT_EDGE)
        {
          yy = py+(y[i]-py)*(CL_XMIN-px)/(x[i]-px);
          xx = CL_XMIN;
        }
        else if (c & RIGHT_EDGE)
        {
          yy = py+(y[i]-py)*(CL_XMAX-px)/(x[i]-px);
          xx = CL_XMAX;
        }
        else if (c & BOTTOM_EDGE)
        {
          xx = px+(x[i]-px)*(CL_YMIN-py)/(y[i]-py);
          yy = CL_YMIN;
        }
        else if (c & TOP_EDGE)
        {
          xx = px+(x[i]-px)*(CL_YMAX-py)/(y[i]-py);
          yy = CL_YMAX;
        }

        if (c == c1)
        {
          x[i-1] = px = xx;
          y[i-1] = py = yy;
          clip_code(xx,yy,&c1);
        }
        else
        {
          x[i] = xx;
          y[i] = yy;
          clip_code(xx,yy,&c2);
        }
      }
      *n = i + 1;
      return *n;
    }
    px = x[i];
    py = y[i];
    c1 = c2;
  }
  return *n;
}
