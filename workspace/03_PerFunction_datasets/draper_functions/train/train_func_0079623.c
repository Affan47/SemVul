drawBevel(int thickness_)
{
  if (canDraw()==MSTrue)
   {
     int offset=highlightThickness();
     MSRect aRect(xDrawingOffset()+offset,yDrawingOffset()+offset+topShadowOffset(),
                  width()-2*offset,height()-topShadowOffset()-2*offset);
     drawBevel(windowForDrawing(),aRect,shadowStyle(),thickness_);
   }
}
