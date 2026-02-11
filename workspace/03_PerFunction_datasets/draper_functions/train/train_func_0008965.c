computeMinimumHeight(void)
{
  int h=highlightThickness()*2+shadowThickness()*2+frameThickness()*2+marginHeight()*2
  +borderHeight()*2+backpageMargin()+labelHeight();
  if (orientation()==Vertical)
   {
     h+=maxTabHeight();
     if (showBinding()==MSTrue) h+=bindingWidth();
   }
  return h;
}
