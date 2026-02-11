draw_smeter(int value,T_BOOL full_refresh)
{
  static int pn_x,pn_y,pn_w,pn_h;
  static T_U8 x1[101],y1[101],x2[101],y2[101];
  static int i=1;


  if(i)
  {
    full_refresh=1;


    for(i=0;i<=100;i++)
      calculate_smeter_needle_coordinates(i,&x1[i],&y1[i],&x2[i],&y2[i]);

    i=0;
  }


  if(full_refresh)
  {
    pn_x=0;
    pn_y=0;
    pn_w=smeter_width;
    pn_h=smeter_height;
  }


  if(value>100)
    value=100;


  gdk_draw_drawable(smeter_drawingarea->window,smeter_gc,
		sharedmem->sidetone_mode?sidetone_bg_pixmap:smeter_bg_pixmap,
		pn_x,pn_y,pn_x,pn_y,pn_w,pn_h);


  gdk_draw_line(smeter_drawingarea->window,smeter_gc,x1[value],y1[value],
		x2[value],y2[value]);


  if(x1[value]<=x2[value])
  {
    pn_x=x1[value]-1;
    pn_w=x2[value]-x1[value]+3;
  }
  else if(x1[value]>x2[value])
  {
    pn_x=x2[value]-1;
    pn_w=x1[value]-x2[value]+3;
  }
  pn_y=y2[value];
  pn_h=y1[value]-y2[value];
}
