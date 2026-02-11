resize(int w_,int h_)
{
  if (width()!=w_||height()!=h_)
   {
     if (w_<=0) w_=1;
     if (h_<=0) h_=1;
     if (w_>=USHRT_MAX) w_=width();
     if (h_>=USHRT_MAX) h_=height();
     if (w_>0) MSRect::width(w_);
     if (h_>0) MSRect::height(h_);

     if (_window!=0) XResizeWindow(display(),_window,width(),height());
     configure();
     childConfigureNotify();
   }
}
