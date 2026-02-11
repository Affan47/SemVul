rk(ColumnVector& ret, const ColumnVector& y, const ColumnVector& dy, float x, float h, const Derivative& deriv,const ColumnVector& paramvalues)
{
  Tracer tr("rk");

  float hh=h*0.5;
  float xh=x+hh;


  ColumnVector yt=y+hh*dy;


  ColumnVector dyt = deriv.evaluate(xh,yt,paramvalues);
  yt=y+hh*dyt;


  ColumnVector dym = deriv.evaluate(xh,yt,paramvalues);
  yt=y+h*dym;
  dym=dym+dyt;


  dyt = deriv.evaluate(x+h,yt,paramvalues);


  ret = y+h*(dy+dyt+2*dym)/6;
}
