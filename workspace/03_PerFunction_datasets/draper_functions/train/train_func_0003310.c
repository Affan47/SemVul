setIdColAcol() {


  int idqNow = (id2 == 21) ? id1 : id2;
  int idqStar = (idqNow > 0) ? idRes : -idRes;
  setId( id1, id2, idqStar);


  if (id1 == idqNow) setColAcol( 1, 0, 2, 1, 2, 0);
  else               setColAcol( 2, 1, 1, 0, 2, 0);
  if (idqNow < 0) swapColAcol();

}
