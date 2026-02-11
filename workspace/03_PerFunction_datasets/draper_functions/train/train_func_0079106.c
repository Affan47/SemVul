get_line(int fy,
                        const GRect &required_red,
                        const GRect &provided_input,
                        const GBitmap &input )
{
  if (fy < required_red.ymin)
    fy = required_red.ymin;
  else if (fy >= required_red.ymax)
    fy = required_red.ymax - 1;

  if (fy == l2)
    return p2;
  if (fy == l1)
    return p1;

  unsigned char *p = p1;
  p1 = p2;
  l1 = l2;
  p2 = p;
  l2 = fy;
  if (xshift==0 && yshift==0)
    {

      int dx = required_red.xmin-provided_input.xmin;
      int dx1 = required_red.xmax-provided_input.xmin;
      const unsigned char *inp1 = input[fy-provided_input.ymin] + dx;
      while (dx++ < dx1)
        *p++ = conv[*inp1++];
      return p2;
    }
  else
    {

      GRect line;
      line.xmin = required_red.xmin << xshift;
      line.xmax = required_red.xmax << xshift;
      line.ymin = fy << yshift;
      line.ymax = (fy+1) << yshift;
      line.intersect(line, provided_input);
      line.translate(-provided_input.xmin, -provided_input.ymin);

      const unsigned char *botline = input[line.ymin];
      int rowsize = input.rowsize();
      int sw = 1<<xshift;
      int div = xshift+yshift;
      int rnd = 1<<(div-1);

      for (int x=line.xmin; x<line.xmax; x+=sw,p++)
        {
          int g=0, s=0;
          const unsigned char *inp0 = botline + x;
          int sy1 = mini(line.height(), (1<<yshift));
          for (int sy=0; sy<sy1; sy++,inp0+=rowsize)
	    {
	      const unsigned char *inp1;
	      const unsigned char *inp2 = inp0 + mini(x+sw, line.xmax) - x;
	      for (inp1=inp0; inp1<inp2; inp1++)
		{
		  g += conv[*inp1];
		  s += 1;
		}
	    }
          if (s == rnd+rnd)
            *p = (g+rnd)>>div;
          else
            *p = (g+s/2)/s;
        }

      return p2;
    }
}
