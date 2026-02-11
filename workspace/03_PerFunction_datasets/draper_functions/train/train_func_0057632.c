drawSliderTitles(void)
{
  int offset=highlightThickness()+shadowThickness();
  int x,len,w,y,center=x_org()+slider()->width()/2;
  XFontStruct *fontInfo;
  GC gc=XCreateGC(display(),window(),0,0);

  if (mintitle().maxLength()>0)
   {
     fontInfo=(XFontStruct *)server()->fontStruct(mintitleFont());
     XSetFont(display(),gc,mintitleFont());
     XSetForeground(display(),gc,mintitleForeground());
     y=MSCenter&mintitleAlignment()?y_end()+labelSpacing():y_end()-mintitleHeight();
     y+=fontInfo->ascent;
     for (int i=0;i<mintitle().length();i++)
      {
        len=mintitle()[i].length();
        const char *cp=mintitle()[i].string();
	w=XTextWidth(fontInfo,cp,len);
	x=MSCenter&mintitleAlignment()?center-w/2:MSLeft&mintitleAlignment()?x_org()-w:x_end();
	XDrawString(display(),window(),gc,fontInfo,x,y,cp,len);
	y+=fontInfo->ascent+fontInfo->descent;
      }
   }
  if (maxtitle().maxLength()!=0)
   {
     fontInfo=(XFontStruct *)server()->fontStruct(maxtitleFont());
     XSetFont(display(),gc,maxtitleFont());
     y=MSCenter&maxtitleAlignment()?y_org()-maxtitleHeight():y_org();
     XSetForeground(display(),gc,maxtitleForeground());
     y+=fontInfo->ascent;
     for (int i=0;i<maxtitle().length();i++)
      {
	len=maxtitle()[i].length();
	const char *cp=maxtitle()[i].string();
	w=XTextWidth(fontInfo,cp,len);
	x=MSCenter&maxtitleAlignment()?center-w/2:MSLeft&maxtitleAlignment()?x_org()-w:x_end();
	XDrawString(display(),window(),gc,fontInfo,x,y,cp,len);
	y+=fontInfo->ascent+fontInfo->descent;
      }
   }
  XFreeGC(display(),gc);
}
