setInternal (int idResIn, int id1In, int id2In, int id3In,
  int idIntIn, int idInt2In) {

  setInternal2(idResIn, id1In, id2In, id3In, idIntIn);

  idInt2 = idInt2In;
  mInt = particleDataPtr->m0(idInt);
  gammaInt = particleDataPtr->mWidth(idInt);
  mInt2 = particleDataPtr->m0(idInt2);
  gammaInt2 = particleDataPtr->mWidth(idInt2);

  iX = coupSUSYPtr->typeNeut(idRes);
  iQ = (id3+1)/2;
  iSq  = (idInt>1000000)? 3 + (idInt%10+1)/2 :  (idInt%10+1)/2;
  iSq2 = (idInt2>1000000)? 3 + (idInt2%10+1)/2 :  (idInt2%10+1)/2;
  isSqDown = (idIntIn % 2 == 1)? true : false;
  m1 = particleDataPtr->m0(id1);
  m2 = particleDataPtr->m0(id2);
  m3 = particleDataPtr->m0(id3);
  return;
}
