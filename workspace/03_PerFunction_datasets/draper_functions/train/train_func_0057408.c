init_self()
{
  double g1 = g_ewald, g2 = g1*g1, g3 = g1*g2;
  const double qscale = force->qqrd2e * scale;

  memset(energy_self, 0, EWALD_NFUNCS*sizeof(double));
  memset(virial_self, 0, EWALD_NFUNCS*sizeof(double));

  if (function[0]) {
    virial_self[0] = -0.5*MY_PI*qscale/(g2*volume)*sum[0].x*sum[0].x;
    energy_self[0] = sum[0].x2*qscale*g1/MY_PIS-virial_self[0];
  }
  if (function[1]) {
    virial_self[1] = MY_PI*MY_PIS*g3/(6.0*volume)*sum[1].x*sum[1].x;
    energy_self[1] = -sum[1].x2*g3*g3/12.0+virial_self[1];
  }
  if (function[2]) {
    virial_self[2] = MY_PI*MY_PIS*g3/(48.0*volume)*(sum[2].x*sum[8].x+
        sum[3].x*sum[7].x+sum[4].x*sum[6].x+0.5*sum[5].x*sum[5].x);
    energy_self[2] = -sum[2].x2*g3*g3/3.0+virial_self[2];
  }
  if (function[3]) {
    virial_self[3] = 0;
    energy_self[3] = sum[9].x2*mumurd2e*2.0*g3/3.0/MY_PIS-virial_self[3];
  }
}
