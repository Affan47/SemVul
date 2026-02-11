draw_meter_y (Display *dpy, Window window, struct state *st, int i, int alone)
{
  XWindowAttributes xgwa;
  int y1,y2,x,h1,h2,w;
  XGetWindowAttributes (dpy, window, &xgwa);

  if(xgwa.height < BAR_SIZE*st->npoints){
    x = i*(xgwa.height/st->npoints);
    w = (xgwa.height/st->npoints) - 2;
  }
  else{
    x = BAR_SIZE*i;
    w = BAR_SIZE - 2;
  }

  if(alone)
    {
      y1 = xgwa.height/2;
      y2 = y1;
    }
  else
    {
      y1 = i*(w+2);
      if(y1 < i)
        y1 = i;
      y2 = y1;
    }

  if(x < 1) x = i;
  if(w < 1) w = 1;

  h1 = (int)(20*st->y_vels[i]);
  h2 = (int)(20*st->balls[i].vy);
  st->y_vels[i] = st->balls[i].vy;

  if (h1<0) {
    h1=-h1;
    y1=y1-h1;
  }
  if (h2<0) {
    h2=-h2;
    y2=y2-h2;
  }
  XDrawRectangle(dpy,window,st->erase_gc,x,y1+(w+2)/2,w,h1);
  XDrawRectangle(dpy,window,st->draw_gc,x,y2+(w+2)/2,w,h2);
}
