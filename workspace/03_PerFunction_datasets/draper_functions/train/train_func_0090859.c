winDrawPoint(i,j,pch)
INT i, j, pch;
{ switch(pch)
  { case 1:
      XDrawArc(dpy,win[cw],myGC,i-2,j-2,5,5,0,360*64);
      return;
    case 2:
      XDrawLine(dpy,win[cw],myGC,i-2,j,i+2,j);
      XDrawLine(dpy,win[cw],myGC,i,j-2,i,j+2);
      return;
    case 3:
      XDrawLine(dpy,win[cw],myGC,i-2,j-2,i+2,j+2);
      XDrawLine(dpy,win[cw],myGC,i+2,j-2,i-2,j+2);
      return;
  }
}
