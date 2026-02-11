force_torque(double *vsold, double *vsnew,
                          double *xs, double *xb,
                          double *fb, double *tb)
{
  double dpdt[3],xs_xb[3];

  double factor = mass_srd / dt_big / force->ftm2v;
  dpdt[0] = factor * (vsnew[0] - vsold[0]);
  dpdt[1] = factor * (vsnew[1] - vsold[1]);
  dpdt[2] = factor * (vsnew[2] - vsold[2]);

  fb[0] -= dpdt[0];
  fb[1] -= dpdt[1];
  fb[2] -= dpdt[2];


  if (tb) {
    xs_xb[0] = xs[0]-xb[0];
    xs_xb[1] = xs[1]-xb[1];
    xs_xb[2] = xs[2]-xb[2];
    tb[0] -= xs_xb[1]*dpdt[2] - xs_xb[2]*dpdt[1];
    tb[1] -= xs_xb[2]*dpdt[0] - xs_xb[0]*dpdt[2];
    tb[2] -= xs_xb[0]*dpdt[1] - xs_xb[1]*dpdt[0];
  }
}
