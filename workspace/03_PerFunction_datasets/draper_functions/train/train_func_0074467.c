numColumns(int row_) const
{
  A a = getTitle();

  if (a!=0&&row_<numRows())
   {
     int type = a->t;
     int rank = a->r;
     I *data =  a->p;

     if (type==Et)
      {
        P p; p.i=data;
	A ra=p.a[row_];
	return (ra->r==0)?1:(int)ra->d[0];
      }
     else if (type==Ct)
      {
        if (rank==0) return 1;
        else if (rank==1) return (int)a->d[0];
	else return (int)a->d[1];
      }
   }
  return 0;
}
