init(void)
{
  _textGC=0;
  _textFontStruct=0;
  _alignment=MSCenter;
  _stipple=new MSPixmap(server(),MSPixmap::ForegroundFiftyPixmap,1,0,1);

  XGCValues values;
  values.foreground=foreground();
  values.background=background();
  values.font=font();
  values.stipple=stipple()->pixmap();
  values.fill_style = FillSolid;
  _textGC=XCreateGC(display(),window(),
		    (GCForeground|GCBackground|GCFont|GCStipple|GCFillStyle),
		    &values);
  _textFontStruct=(XFontStruct *)server()->fontStruct(font());
}
