weightDecay( Event& process, int iResBeg,
  int iResEnd) {


  int idMother = process[process[iResBeg].mother1()].idAbs();


  if (iResBeg == 5 && iResEnd == 5) {
    double mr     = 4. * pow2(process[6].m()) / sH;
    double cosThe = (process[3].p() - process[4].p())
      * (process[7].p() - process[6].p()) / (sH * sqrtpos(1. - mr));
    double wt     = 1. + pow2(cosThe) + mr * (1. - pow2(cosThe));
    return 0.5 * wt;
  }


  if (idMother == 6)
    return weightTopDecay( process, iResBeg, iResEnd);


  return 1.;

}
