calc_mod_dp2(double z1, double z2, double p_coef[])
{
  int i;
  double temp,mp1,mp2;

  mp1=0;
  mp2=0;
  for(i=deg_p;i>=2;i--)
  {
    add(mp1,mp2,i*p_coef[(i-2)*2],i*p_coef[(i-2)*2+1]);
    mult(mp1,mp2,z1,z2);
  }
  add(mp1,mp2,1,0);
  return mp1*mp1+mp2*mp2;
}
