highlightColor(unsigned long pixel_)
{
  if (pixel_!=highlightColor())
   {
     _highlightColor=pixel_;
     highlightMSGC().foreground(highlightColor());
     if (highlighted()==MSTrue) drawHighlight();
   }
}
