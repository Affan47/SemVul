rowLength(unsigned row_) const
{
  if (MSView::model()!=0&&row_<list().length())
   {
     const char *pString=list()(row_).symbolName();
     return (pString!=0)?strlen(pString):0;
   }
  return 0;
}
