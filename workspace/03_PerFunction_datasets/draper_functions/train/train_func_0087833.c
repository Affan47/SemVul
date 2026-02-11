acri(lk,t0,t2,pen)
double lk, t0, t2, pen;
{ double y;


  y = (MAX(-2*lk,t0-t2)+pen*t2)/t0;
  return(y);
}
