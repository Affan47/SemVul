LabelIconWindow(PagerWindow *t)
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
      XChangeGC(dpy,StdGC,Globalgcm,&Globalgcv);

    }
  XClearWindow(dpy, t->IconView);
#undef FONTSET
#define FONTSET windowFontset
  XDrawImageString (dpy, t->IconView,tgc,2,windowFont->ascent+2 ,
	       t->icon_name, strlen(t->icon_name));

}
