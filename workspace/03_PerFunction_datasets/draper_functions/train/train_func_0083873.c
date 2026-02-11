update_rs(x)
double x;
{
  if (lf_status != LF_OK) return(x);
  robscale = exp(x);
  lfiter(rob_lf,rob_des);
  if (lf_status != LF_OK) return(x);

  return(log(robustscale(rob_lf,rob_des)));
}
