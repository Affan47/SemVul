setIdColAcol(){

  int qIdx    = config / 2;
  int idTmp[3] = { 21, 21, 21 };
  idTmp[qIdx]  = (id1 == 21) ? id2 : id1;
  setId( id1, id2, idTmp[0], idTmp[1], idTmp[2]);


  if      (qIdx == 0) setColAcol(1, 0, 2, 1, 4, 0, 3, 4, 2, 3);
  else if (qIdx == 1) setColAcol(1, 0, 2, 1, 3, 4, 4, 0, 2, 3);
  else                setColAcol(1, 0, 2, 1, 3, 4, 2, 3, 4, 0);

  if (id1 == 21) {
    swap( colSave[1], colSave[2]);
    swap(acolSave[1], acolSave[2]);
  }

  if (id1 < 0 || id2 < 0) swapColAcol();

}
