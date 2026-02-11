initProc() {


  idHad = 0;
  nameSave = "illegal process";
  if (stateSave == 0) {
    idHad = (idNew == 4) ? 9900443 : 9900553;
    nameSave = (idNew == 4) ? "q g -> ccbar[3S1(8)] q"
      : "q g -> bbbar[3S1(8)] q";
    oniumME = (idNew == 4) ? settingsPtr->parm("Charmonium:OJpsi3S18")
      : settingsPtr->parm("Bottomonium:OUpsilon3S18");
  } else if (stateSave == 1) {
    idHad = (idNew == 4) ? 9900441 : 9900551;
    nameSave = (idNew == 4) ? "q g -> ccbar[1S0(8)] q"
      : "q g -> bbbar[1S0(8)] q";
    oniumME = (idNew == 4) ? settingsPtr->parm("Charmonium:OJpsi1S08")
      : settingsPtr->parm("Bottomonium:OUpsilon1S08");
  } else if (stateSave == 2) {
    idHad = (idNew == 4) ? 9910441 : 9910551;
    nameSave = (idNew == 4) ? "q g -> ccbar[3PJ(8)] q"
      : "q g -> bbbar[3PJ(8)] q";
    oniumME = (idNew == 4) ? settingsPtr->parm("Charmonium:OJpsi3P08")
      : settingsPtr->parm("Bottomonium:OUpsilon3P08");
  }

}
