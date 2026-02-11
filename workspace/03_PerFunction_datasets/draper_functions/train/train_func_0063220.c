labelSpacing(unsigned labelSpacing_)
{
  if (labelSpacing_!=labelSpacing())
   {
     _labelSpacing=labelSpacing_;
     if (firstMap()==MSTrue&&labelAlignment()==MSTop) adjustSize();
   }
}
