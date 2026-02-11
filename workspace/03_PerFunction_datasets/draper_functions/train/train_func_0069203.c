sinfo_table_column_interpolate(const cpl_table* t,
                               const char* name,
                               const double x)
{

  double val1=0;
  double val2=0;
  int x1=0;
  int x2=0;
  double m=0;
  double y=0;
  int status=0;
  int nrow=0;
  nrow=cpl_table_get_nrow(t);
  if ((1<x) && (x<nrow-1)) {
    x1=x-1;
    x2=x+1;
  } else if (x<2) {
    x1=0;
    x2=1;
  } else {
    x1=nrow-2;
    x2=nrow-1;
  }
  check_nomsg(val1=cpl_table_get(t,name,x1,&status));
  check_nomsg(val2=cpl_table_get(t,name,x2,&status));

  m=(val2-val1)/(x2-x1);
  y=val1+m*(x-x1);

  return y;

 cleanup:

  return -1;


}
