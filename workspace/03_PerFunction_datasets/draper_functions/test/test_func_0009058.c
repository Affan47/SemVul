setIdColAcol() {


  id4 = couplingsPtr->V2CKMpick(id1);
  id5 = couplingsPtr->V2CKMpick(id2);
  setId( id1, id2, idRes, id4, id5);


  if (abs(id1) < 9 && abs(id2) < 9 && id1*id2 > 0)
                         setColAcol( 1, 0, 2, 0, 0, 0, 1, 0, 2, 0);
  else if (abs(id1) < 9 && abs(id2) < 9)
                         setColAcol( 1, 0, 0, 2, 0, 0, 1, 0, 0, 2);
  else if (abs(id1) < 9) setColAcol( 1, 0, 0, 0, 0, 0, 1, 0, 0, 0);
  else if (abs(id2) < 9) setColAcol( 0, 0, 1, 0, 0, 0, 0, 0, 1, 0);
  else                   setColAcol( 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  if ( (abs(id1) < 9 && id1 < 0) || (abs(id1) > 10 && id2 < 0) )
    swapColAcol();

}
