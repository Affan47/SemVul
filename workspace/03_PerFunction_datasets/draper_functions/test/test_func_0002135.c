computeXCoord(int row_,int column_,const char *string_,int len_)
{
  int pixmapW=0;


  if (showPixmap()==MSTrue&&pixmap()!=0)
   {
     if (armed()==MSTrue) pixmapW=armedPixmap()->width();
     else if (sensitive()==MSTrue) pixmapW=pixmap()->width();
     else pixmapW=insensitivePixmap()->width();
   }
  return computeXCoordinate(row_,column_,pixmapW,string_,len_);
}
