weightDecay( Event& process, int iResBeg,
  int iResEnd) {


  if (iResBeg != 5 || iResEnd != 5) return 1.;


  double mr1    = pow2(process[6].m()) / sH;
  double mr2    = pow2(process[7].m()) / sH;
  double betaf  = sqrtpos( pow2(1. - mr1 - mr2) - 4. * mr1 * mr2);


  double eps    = (process[3].id() * process[6].id() > 0) ? 1. : -1.;


  double cosThe = (process[3].p() - process[4].p())
    * (process[7].p() - process[6].p()) / (sH * betaf);
  double wtMax  = 4.;
  double wt     = pow2(1. + betaf * eps * cosThe) - pow2(mr1 - mr2);


  return (wt / wtMax);

}
