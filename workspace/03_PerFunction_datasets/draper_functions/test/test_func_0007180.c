weightDecay( Event& process, int iResBeg,
  int iResEnd) {


  int idMother = process[process[iResBeg].mother1()].idAbs();


  if (idMother == 25 || idMother == 35 || idMother == 36)
    return weightHiggsDecay( process, iResBeg, iResEnd);


  if (idMother == 6)
    return weightTopDecay( process, iResBeg, iResEnd);


  return 1.;

}
