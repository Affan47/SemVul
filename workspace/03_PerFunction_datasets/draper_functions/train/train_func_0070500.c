sym_submatrix(int first_row, int last_row) const
{
   REPORT
   Tracer tr("sym_submatrix");
   int a = first_row - 1; int b = last_row - first_row + 1;
   if (a<0 || b<0) Throw(SubMatrixDimensionException());

   return GetSubMatrix( this, a, b, a, b, true);
}
