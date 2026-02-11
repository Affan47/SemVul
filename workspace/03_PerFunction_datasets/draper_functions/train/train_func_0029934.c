redrawImmediately(void)
{
  if (mapped()==MSTrue&&frozen()==MSFalse)
   {
     redrawPixmap()->lock();
     XFillRectangle(display(),redrawPixmap()->pixmap(),backgroundShadowGC(),
		    0,0,panner()->width(),panner()->height());
     drawRows(redrawPixmap()->pixmap(),firstRow(),firstRow()+rows()-1);
     int ht=panner()->highlightThickness();
     MSRect aRect(ht,ht+headingsHeight(),panner()->width()-2*ht,panner()->height()-headingsHeight()-2*ht);
     drawBevel(redrawPixmap()->pixmap(),aRect,panner()->shadowStyle(),panner()->shadowThickness());
     drawDelimiterHeaders(redrawPixmap()->pixmap());
     XCopyArea(display(),redrawPixmap()->pixmap(),panner()->window(),
	       backgroundShadowGC(),
	       0,0,panner()->width(),panner()->height(),0,0);
     moveSelection(selectedRow());
     updateScrollBars();
     XFlush(display());
     redrawPixmap()->unlock();
   }
}
