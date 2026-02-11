xsh_sess2deg(const double sess)
{
  int grad=0;
  int min=0;
  double sec=0;
  double deg=0;
  double rest=sess;
  int sign=1;

  if(sess<0) {
    sign=-1;
    rest=-sess;
  }
  grad=(int)(rest/10000.);
  rest=rest-(double)(grad*10000.);
  min=(int)(rest/100.);
  sec=rest-(double)(min*100.);
  deg=grad+(double)(min/60.)+(double)(sec/3600.);
  deg=sign*deg;

  return deg;

}
