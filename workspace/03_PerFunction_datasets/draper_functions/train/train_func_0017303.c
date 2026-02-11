computeYFontScale(int y_)
{
  double h=tablePageSize(rowPageBreak().length()-1);
  double y=y_+headingHeight();
  int  headers=tableHeaderHeight()+tableFooterHeight();
  if(scaleHeaders()==MSTrue) y+=headers;
  else h-=headers;
  double scale=h/y;
  if (scale<y_printScale()) y_printScale(scale);
}
