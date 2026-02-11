operator()(int m, int n) const
{
   REPORT
   if (n<=0 || m!=n || m>nrows_val || n>ncols_val)
      Throw(IndexException(m,n,*this));
   return store[n-1];
}
