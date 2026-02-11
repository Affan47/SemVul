draw(void)
{
  if (mapped()==MSTrue&&owner()->mapped()==MSTrue&&owner()->owner()->mapped()==MSTrue)
   {
     int ht=highlightThickness();
     int sht=shadowThickness();
     int offset=ht+sht;
     int y=offset+DefaultElevatorBoxHeight;

     if (scrollBar()->style()==MSScrollBar::Openlook)
      {
	drawBackground();
	drawShadow(MSRaised);

	if (height()==DefaultElevatorHeight)
	 {
	   XDrawLine(display(),window(),topShadowGC(),offset,y,width()-2*offset,y);
	   y+=DefaultElevatorBoxHeight;
	   XDrawLine(display(),window(),bottomShadowGC(),offset,y,width()-2*offset,y);
	   drawArrows();
	 }
	else if (height()==MinElevatorHeight)
	 {
	   XDrawLine(display(),window(),bottomShadowGC(),offset,y,width()-2*offset,y);
	   drawArrows();
	 }
      }
     else
      {
        drawRaised();
	XFillRectangle(display(),window(),backgroundShadowGC(),
		       offset,offset,width()-2*offset,height()-2*offset);
        drawArrows();
      }
   }
}
