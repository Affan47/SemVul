drawColumnHeadings(Window window_,int cs_,int ce_)
{
  if (mapped()==MSTrue&&frozen()==MSFalse&&headingsHeight()>0)
   {
     int offset=panner()->highlightThickness()+panner()->shadowThickness();
     int y=offset;
     int x=computeXCoord(cs_);
     int len=0;
     int cw=0;
     int j,w;
     MSRect aRect;

     for (j=cs_;j<=ce_&&j<numColumns();j++)
      {
	MSTableColumn *pTableColumn=tableColumn(j);
	cw=pTableColumn->columnPixelWidth();
	if (pTableColumn->heading().length()>0)
	 {
           len=pTableColumn->columnWidth();
           w=panner()->width()-2*(panner()->shadowThickness()+panner()->highlightThickness());
           XFillRectangle(display(),window_,panner()->backgroundShadowGC(),
                          x,y,(cw>w)?w:cw,headingsHeight()-rowSpacing());
           aRect.configuration(x+columnSpacing(),y+rowSpacing(),
                          (cw>w)?w:cw,headingsHeight()-2*rowSpacing());
	   drawColumnHeading(window_,pTableColumn,aRect,len);
	 }
	x+=cw;
      }
     XBFillRectangle(display(),window_,panner()->bottomShadowGC(),
	 	     offset,offset+headingsHeight()-rowSpacing(),
		     panner()->width()-2*offset,rowSpacing());
   }
}
