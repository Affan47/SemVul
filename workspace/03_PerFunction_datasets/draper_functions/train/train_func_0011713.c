Compute_tabH( real r_ij, int ti, int tj )
{
  int r, tmin, tmax;
  real val, dif, base;
  LR_lookup_table *t;

  tmin  = MIN( ti, tj );
  tmax  = MAX( ti, tj );
  t = &( LR[tmin][tmax] );


  r = (int)(r_ij * t->inv_dx);
  if( r == 0 )  ++r;
  base = (real)(r+1) * t->dx;
  dif = r_ij - base;
  val = ((t->ele[r].d*dif + t->ele[r].c)*dif + t->ele[r].b)*dif +
    t->ele[r].a;
  val *= EV_to_KCALpMOL / C_ele;

  return val;
}
