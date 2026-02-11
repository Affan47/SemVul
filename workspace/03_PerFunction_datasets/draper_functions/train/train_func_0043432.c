checkPanFrames(void)
{
  extern Bool DoHandlePageing;
  int wrapX = (Scr.flags & EdgeWrapX);
  int wrapY = (Scr.flags & EdgeWrapY);


  if((Scr.EdgeScrollY == 0)||(!DoHandlePageing))
    {
      XUnmapWindow(dpy,Scr.PanFrameTop.win);
      Scr.PanFrameTop.isMapped=False;
      XUnmapWindow (dpy,Scr.PanFrameBottom.win);
      Scr.PanFrameBottom.isMapped=False;
    }
  if((Scr.EdgeScrollX == 0)||(!DoHandlePageing))
    {
      XUnmapWindow(dpy,Scr.PanFrameLeft.win);
      Scr.PanFrameLeft.isMapped=False;
      XUnmapWindow (dpy,Scr.PanFrameRight.win);
      Scr.PanFrameRight.isMapped=False;
    }
  if(((Scr.EdgeScrollX == 0)&&(Scr.EdgeScrollY == 0))||(!DoHandlePageing))
    return;


  if (Scr.Vx==0 && Scr.PanFrameLeft.isMapped && (!wrapX))
    {
      XUnmapWindow(dpy,Scr.PanFrameLeft.win);
      Scr.PanFrameLeft.isMapped=False;
    }
  else if (Scr.Vx > 0 && Scr.PanFrameLeft.isMapped==False)
    {
      XMapRaised(dpy,Scr.PanFrameLeft.win);
      Scr.PanFrameLeft.isMapped=True;
    }

  if (Scr.Vx == Scr.VxMax && Scr.PanFrameRight.isMapped && (!wrapX))
    {
      XUnmapWindow (dpy,Scr.PanFrameRight.win);
      Scr.PanFrameRight.isMapped=False;
    }
  else if (Scr.Vx < Scr.VxMax && Scr.PanFrameRight.isMapped==False)
    {
      XMapRaised(dpy,Scr.PanFrameRight.win);
      Scr.PanFrameRight.isMapped=True;
    }

  if (Scr.Vy==0 && Scr.PanFrameTop.isMapped && (!wrapY))
    {
      XUnmapWindow(dpy,Scr.PanFrameTop.win);
      Scr.PanFrameTop.isMapped=False;
    }
  else if (Scr.Vy > 0 && Scr.PanFrameTop.isMapped==False)
    {
      XMapRaised(dpy,Scr.PanFrameTop.win);
      Scr.PanFrameTop.isMapped=True;
    }

  if (Scr.Vy == Scr.VyMax && Scr.PanFrameBottom.isMapped && (!wrapY))
    {
      XUnmapWindow (dpy,Scr.PanFrameBottom.win);
      Scr.PanFrameBottom.isMapped=False;
    }
  else if (Scr.Vy < Scr.VyMax && Scr.PanFrameBottom.isMapped==False)
    {
      XMapRaised(dpy,Scr.PanFrameBottom.win);
      Scr.PanFrameBottom.isMapped=True;
    }
}
