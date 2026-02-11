defaultNumVisible(void)
{
  if ((sizeState()&RowsValid)!=RowsValid)
   {
     _rows=5;
     _rows=(rows()<=numRows())?rows():numRows();
   }
  if ((sizeState()&ColsValid)!=ColsValid)
   {
     _columns=2;
     _columns=(columns()<=numColumns())?columns():numColumns();
     _columns=(columns()<=0)?0:columns();
   }
}
