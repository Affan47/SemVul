labelSpacing(int labelSpacing_)
{
  if (_labelSpacing!=labelSpacing_)
   {
     _labelSpacing=labelSpacing_;
     if (dynamic()==MSTrue) computeSize();
     else redraw();
   }
}
