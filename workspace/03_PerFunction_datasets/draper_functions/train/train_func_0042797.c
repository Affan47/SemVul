LabelWindow(PagerWindow *t)
{
  XGCValues Globalgcv;
  unsigned long Globalgcm;
  GC tgc;

  if(windowFont == NULL)
    {
      return;
    }
  if(t->icon_name == NULL)
    {
      return;
    }
  if(t == FocusWin)
    {
      tgc = FocusGC;
    }
  else
    {
      tgc = StdGC;
      Globalgcv.foreground = t->text;
      Globalgcv.background = t->back;
      Globalgcm = GCForeground|GCBackground;
      XChangeGC(dpy, StdGC,Globalgcm,&Globalgcv);
    }
#undef FONTSET
#define FONTSET windowFontset
  if(t->PagerView != None)
    {
      XClearWindow(dpy, t->PagerView);
      XDrawImageString (dpy, t->PagerView,tgc,2,windowFont->ascent+2 ,
			t->icon_name, strlen(t->icon_name));
    }
}
