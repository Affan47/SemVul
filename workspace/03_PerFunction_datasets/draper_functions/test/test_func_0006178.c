setCablePixmap(void)
{
  if (firstMap()==MSTrue)
   {
     if (cablePixmap()!=0) delete _cablePixmap;
     if (style()==MSScrollBar::Openlook)
      {
	_cablePixmap=new MSPixmap(server(),MSPixmap::ForegroundFiftyPixmap,
				  bottomShadowColor(),background());
	XSetTile(display(),bottomShadowGC(),cablePixmap()->pixmap());
      }
     else _cablePixmap=0;
   }
}
