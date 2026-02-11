redraw(void)
{
  if (mapped()==MSTrue)
   {
     redrawPixmap()->lock();
     XFillRectangle(display(),redrawPixmap()->pixmap(),backgroundShadowGC(),
		    0,0,width(),height());
     int ht=highlightThickness();
     MSRect aRect(ht,ht+topShadowOffset(),width()-2*ht,height()-topShadowOffset()-2*ht);
     drawBevel(redrawPixmap()->pixmap(),aRect,shadowStyle(),shadowThickness());
     drawBinding(redrawPixmap()->pixmap());
     drawBackpage(redrawPixmap()->pixmap());
     drawFrameShadow(redrawPixmap()->pixmap());
     XCopyArea(display(),redrawPixmap()->pixmap(),window(),backgroundShadowGC(),0,0,width(),height(),0,0);
     redrawPixmap()->unlock();
   }
}
