DrawGrid(int i, int erase)
{
  int y, y1, y2, x, x1, x2,d,hor_off,w;
  int MaxW,MaxH;
  char str[15], *ptr;

  if((i < 0 ) ||(i >= ndesks))
    return;

  MaxW = (Scr.VxMax + Scr.MyDisplayWidth);
  MaxH = Scr.VyMax + Scr.MyDisplayHeight;

  x = Scr.MyDisplayWidth;
  y1 = 0;
  y2 = desk_h;
  while(x < MaxW)
    {
      x1 = x*desk_w/MaxW;
      XDrawLine(dpy,Desks[i].w,NormalGC,x1,y1,x1,y2);
      x += Scr.MyDisplayWidth;
    }

  y = Scr.MyDisplayHeight;
  x1 = 0;
  x2 = desk_w;
  while(y < MaxH)
    {
      y1 = y*(desk_h)/MaxH;
      XDrawLine(dpy,Desks[i].w,NormalGC,x1,y1,x2,y1);
      y += Scr.MyDisplayHeight;
    }
  if((Scr.CurrentDesk - desk1)  == i)
    {
      if(uselabel)
	XFillRectangle(dpy,Desks[i].title_w,HiliteGC,
		       0,0,desk_w,label_h -1);
    }
  else
    {
      if(uselabel && erase)
	XClearArea(dpy,Desks[i].title_w,
		   0,0,desk_w,label_h - 1,False);
    }

  d = desk1+i;
  ptr = Desks[i].label;
  w=XTextWidth(font,ptr,strlen(ptr));
  if( w > desk_w)
    {
      sprintf(str,"%d",d);
      ptr = str;
      w=XTextWidth(font,ptr,strlen(ptr));
    }
  if((w<= desk_w)&&(uselabel))
    {
      hor_off = (desk_w -w)/2;
#undef FONTSET
#define FONTSET fontset
      if(i == (Scr.CurrentDesk - desk1))
	XDrawString (dpy, Desks[i].title_w,rvGC,hor_off,font->ascent +1 ,
		     ptr, strlen(ptr));
      else
	XDrawString (dpy, Desks[i].title_w,NormalGC,hor_off,font->ascent+1  ,
		     ptr, strlen(ptr));
    }
}
