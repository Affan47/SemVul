calculateColumnHeadingsHeight(void)
{
  MSTableColumn *pTableColumn;
  Font           fid;
  int            th,max=0;
  unsigned       n=numColumns();
  for (unsigned i=0;i<n;i++)
   {
     pTableColumn=tableColumn(i);
     fid=pTableColumn->headingFont();
     pTableColumn->headingFontStruct((XFontStruct *)server()->fontStruct(fid));
     th=pTableColumn->headingHeight();
     max=(th>max)?th:max;
   }
  max=(max>0)?max+(rowSpacing()<<1):0;
  columnHeadingsHeight(max);
}
