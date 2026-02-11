scrollRight(int count_)
{
  int numCols=actualNumColumns();
  if (firstColumn()+columns()<numCols&&count_>0)
   {
     if (firstColumn()+columns()+count_>numCols)
      {
        count_=numCols-(firstColumn()+columns());
      }
     _firstColumn+=count_;
     redrawImmediately();
     firstColumnChangeNotify();
   }
}
