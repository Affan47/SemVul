breakText(MSParagraph *x_)
{
  if (_breakTextList==0) _breakTextList=new MSPointerArray<MSParagraph>;
  breakTextList()->add(x_);
}
