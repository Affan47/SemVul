setIdColAcol() {


  setId( id1, id2, idHLR, -idHLR);


  if (id1 > 0) swapTU = true;


  if (abs(id1) < 9) setColAcol( 1, 0, 0, 1, 0, 0, 0, 0);
  else              setColAcol( 0, 0, 0, 0, 0, 0, 0, 0);
  if (id1 < 0) swapColAcol();

}
