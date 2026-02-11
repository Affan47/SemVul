armedPixmap(const MSPixmap &pixmap_)
{
  MSPixmap *tmp=_pixmap;
  if (pixmap_.server()==server())
  _armedPixmap=new MSPixmap(pixmap_);
  else
   {
     MSMessageLog::warningMessage("Warning :armedPixmap supplied for MSToggleMenuItem is invalid, using default");
     _armedPixmap=createDefaultPixmap(pixmap_.width(),pixmap_.height(),
				      pixmap_.foreground(),pixmap_.background());
   }
  if (tmp!=0) delete tmp;
  if (dynamic()==MSTrue) computeSize();
  else if (owner()->mapped()==MSTrue)
   {
     redraw();
     (armed()==MSTrue)?drawSunken():drawRaised();
   }
}
