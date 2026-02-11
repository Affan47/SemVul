XDrawRectangle(Display *dpy_,Window id_,GC gc_,
				    int x_,int y_,int w_,int h_)
{
  if (_outputMode==Draw) ::XDrawRectangle(dpy_,id_,gc_,x_,y_,w_,h_);
  else if (displayPrintMode()==MSP::PPM)
   {
     int x=x_+_displayPrint._displayPrint->x_org();
     int y=y_+_displayPrint._displayPrint->y_org();
     ::XDrawRectangle(dpy_,displayPrintPixmap(),gc_,x,y,w_,h_);
   }
  else _displayPrint._displayPrint->printRectangle(gc_,x_,y_,w_,h_);
}
