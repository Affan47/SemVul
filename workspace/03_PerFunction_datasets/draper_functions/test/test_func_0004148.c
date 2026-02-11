ConstrainSize (FvwmWindow *tmp_win, int *widthp, int *heightp)
{
#define makemult(a,b) ((b==1) ? (a) : (((int)((a)/(b))) * (b)) )
#define _min(a,b) (((a) < (b)) ? (a) : (b))
    int minWidth, minHeight, maxWidth, maxHeight, xinc, yinc, delta;
    int baseWidth, baseHeight;
    int dwidth = *widthp, dheight = *heightp;

    dwidth -= 2 *tmp_win->boundary_width;
    dheight -= (tmp_win->title_height + 2*tmp_win->boundary_width);

    minWidth = tmp_win->hints.min_width;
    minHeight = tmp_win->hints.min_height;

    baseWidth = tmp_win->hints.base_width;
    baseHeight = tmp_win->hints.base_height;

    maxWidth = tmp_win->hints.max_width;
    maxHeight =  tmp_win->hints.max_height;


    xinc = tmp_win->hints.width_inc;
    yinc = tmp_win->hints.height_inc;


    if (dwidth < minWidth) dwidth = minWidth;
    if (dheight < minHeight) dheight = minHeight;

    if (dwidth > maxWidth) dwidth = maxWidth;
    if (dheight > maxHeight) dheight = maxHeight;


    dwidth = ((dwidth - baseWidth) / xinc * xinc) + baseWidth;
    dheight = ((dheight - baseHeight) / yinc * yinc) + baseHeight;


#define maxAspectX tmp_win->hints.max_aspect.x
#define maxAspectY tmp_win->hints.max_aspect.y
#define minAspectX tmp_win->hints.min_aspect.x
#define minAspectY tmp_win->hints.min_aspect.y


    if (tmp_win->hints.flags & PAspect)
      {
        if (minAspectX * dheight > minAspectY * dwidth)
	  {
            delta = makemult(minAspectX * dheight / minAspectY - dwidth,
                             xinc);
            if (dwidth + delta <= maxWidth)
	      dwidth += delta;
            else
	      {
                delta = makemult(dheight - dwidth*minAspectY/minAspectX,
                                 yinc);
                if (dheight - delta >= minHeight) dheight -= delta;
	      }
	  }

        if (maxAspectX * dheight < maxAspectY * dwidth)
	  {
            delta = makemult(dwidth * maxAspectY / maxAspectX - dheight,
                             yinc);
            if (dheight + delta <= maxHeight)
	      dheight += delta;
            else
	      {
                delta = makemult(dwidth - maxAspectX*dheight/maxAspectY,
                                 xinc);
                if (dwidth - delta >= minWidth) dwidth -= delta;
	      }
	  }
      }


    *widthp = dwidth + 2*tmp_win->boundary_width;
    *heightp = dheight + tmp_win->title_height + 2*tmp_win->boundary_width;
    return;
}
