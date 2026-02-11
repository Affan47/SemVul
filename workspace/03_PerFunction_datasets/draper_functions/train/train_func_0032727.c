ChangeMainColorset (int i)
{

  if (x11base->colorset < 0) {
    PictureFreeColors(dpy,Pcmap,&x11base->TabColor[fore],1,0,True);
    PictureFreeColors(dpy,Pcmap,&x11base->TabColor[back],1,0,True);
    PictureFreeColors(dpy,Pcmap,&x11base->TabColor[hili],1,0,True);
    PictureFreeColors(dpy,Pcmap,&x11base->TabColor[shad],1,0,True);
  }
  x11base->colorset = i;
  AllocColorset(i);
  x11base->TabColor[fore] = Colorset[i].fg;
  x11base->TabColor[back] = Colorset[i].bg;
  x11base->TabColor[hili] = Colorset[i].hilite;
  x11base->TabColor[shad] = Colorset[i].shadow;
  SetWindowBackground(dpy, x11base->win,x11base->size.width,x11base->size.height,
		      &Colorset[i], Pdepth, x11base->gc, True);
}
