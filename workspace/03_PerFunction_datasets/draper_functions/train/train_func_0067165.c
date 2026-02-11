rad_forceik(Param *paramk, double rsq2, double *delrk,
        double conjug, double radtot)
{
  int nm;
  double  rik, fc1k, fcp1k;
  double pradk, ffkk2, fktmp[3];
  double radcut = comb_fcch(radtot);
  double dradcut = comb_fcch_d(radtot);

  for (nm=0; nm<3; nm++) {
    fi_rad[nm] =  fk_rad[nm] = 0.0;
  }
    radtmp =0.0;

  rik = sqrt(rsq2);

  fc1k = comb_fc(rik, paramk);
  fcp1k = comb_fc_d(rik,paramk);

  pradk = brad[3]*fcp1k*radcut*paramk->pcross*2.0*conjug;
  radtmp= brad[3]*fc1k*dradcut*paramk->pcross*2.0*conjug;

  ffkk2 = -pradk/rik;

  for (nm=0; nm<3; nm++) {
    fktmp[nm] = - ffkk2 * delrk[nm];
  }

  for (nm=0; nm<3; nm++) {
    fi_rad[nm] =  fktmp[nm];
    fk_rad[nm] = -fktmp[nm];
  }
}
