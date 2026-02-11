addHeader(const MSParagraph& aParagraph_)
{
  MSParagraph *aParagraph=new MSParagraph(aParagraph_);
  aParagraph->pageAlignment(MSNone);
  _textList.add(aParagraph);
  _headerList.add(aParagraph);
  return *aParagraph;
}
