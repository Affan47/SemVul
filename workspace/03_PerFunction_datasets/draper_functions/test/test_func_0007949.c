updateFirstColumn(int column_)
{
  if (column_<0) column_=0;
  else if (column_>=numColumns()) column_=numColumns()-1;

  if (column_>=fixedColumns()&&column_<numColumns()&&column_!=firstColumn())
   {
     _firstColumn=column_;
     unsigned oldFirstColumn=firstColumn();
     _columns=computeNumVisibleColumns();
     adjustFirstColumn();
     redrawImmediately();
     if (selectedColumn()>=0&&selectedColumn()>=numColumns()) selectedColumn(numColumns()-1);
     if (oldFirstColumn==firstColumn()) firstColumnChangeNotify();
   }
}
