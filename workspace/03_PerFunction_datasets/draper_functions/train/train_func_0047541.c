initProc() {


  coupSUSYPtr = (CoupSUSY*) couplingsPtr;


  if (id4 % 2 == 0) {
    nameSave = "q g -> " + particleDataPtr->name(id3) + " "
      + particleDataPtr->name(id4) + " + c.c. (q=u,c)";
  }
  else {
    nameSave = "q g -> " + particleDataPtr->name(id3) + " "
      + particleDataPtr->name(id4) + " + c.c. (q=d,s,b)";
  }


  openFracPair = particleDataPtr->resOpenFrac(id3, id4);

}
