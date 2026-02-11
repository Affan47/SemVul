weightDecay( Event& process, int iResBeg,
  int iResEnd) {


  if (iResBeg != 5 && iResEnd != 5) return 1.;


  double mr1    = pow2(process[7].m() / process[5].m());
  double mr2    = pow2(process[8].m() / process[5].m());


  int  idAbs3 = process[7].idAbs();
  Vec4 pLStarCom = (idAbs3 < 20) ? process[7].p() : process[8].p();
  pLStarCom.bstback(process[5].p());
  double cosThe = costheta(pLStarCom, process[5].p());
  double wt     = 1.;


  int idBoson   = (idAbs3 < 20) ? process[8].idAbs() : process[7].idAbs();
  if (idBoson == 22) {
    wt          = 0.5 * (1. + cosThe);
  } else if (idBoson == 23 || idBoson == 24) {
    double mrB  = (idAbs3 < 20) ? mr2 : mr1;
    double kTrm = 0.5 * (mrB * (1. - cosThe));
    wt          = (1. + cosThe + kTrm) / (2 + mrB);
  }


  return wt;
}
