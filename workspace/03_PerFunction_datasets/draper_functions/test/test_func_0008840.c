numRows(void) const
{
  A a = getTitle();
  if (a!=0)
   {
     int type = a->t;
     int rank = a->r;
     int n = a->n;

     if (type==Et) return (int)n;
     else if (type==Ct) return (rank<=1)?1:(int)a->d[0];
   }
  return 0;
}
