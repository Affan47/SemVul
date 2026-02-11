redrawImmediately(void)
{
  if (mapped()==MSTrue&&frozen()==MSFalse)
   {
     redrawPixmap()->lock();
     XFillRectangle(display(),redrawPixmap()->pixmap(),backgroundShadowGC(),
		    0,0,panner()->width(),panner()->height());
     drawRows(redrawPixmap()->pixmap(),firstRow(),lastRow());
     drawHeadings(redrawPixmap()->pixmap());
     drawLabels(redrawPixmap()->pixmap(),firstRow(),lastRow());
     cleanUpBottom(redrawPixmap()->pixmap());
     int ht=panner()->highlightThickness();
     MSRect aRect(ht,ht,panner()->width()-2*ht,panner()->height()-2*ht);
     drawBevel(redrawPixmap()->pixmap(),
               aRect,panner()->shadowStyle(),panner()->shadowThickness());
     XCopyArea(display(),redrawPixmap()->pixmap(),panner()->window(),
	       backgroundShadowGC(),
	       0,0,panner()->width(),panner()->height(),0,0);
     moveSelection(selectedRow(),selectedColumn());
     updateScrollBars();
     XFlush(display());
     redrawPixmap()->unlock();
   }

}
