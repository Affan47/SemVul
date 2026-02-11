InvertMatrix(Matrix& A, Matrix& A_inv)
{
   int n = A.nrows();
   if (n != A.ncols()) Throw(Logic_error("Not square"));
   SimpleIntArray Indx(n);
   ColumnVector V(n);
   A_inv.ReSize(n,n);
   int i = InvertMatrix(
      C_sub2(A),
      n,
      V.data(),
      Indx.Data(),
      C_sub2(A_inv) );
   if (i) Throw(Runtime_error("Singular matrix"));
}
