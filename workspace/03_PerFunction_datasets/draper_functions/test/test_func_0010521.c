flipNeighborsGet(Nrrd *nTriWithVert, Nrrd *nVertWithTri,
                 unsigned int neighGot[3], unsigned int neighInfo[3][3],
                 unsigned int *intxBuff, unsigned int triIdx) {

  unsigned int intxNum, vertA, vertB, neighIdx, maxTriPerVert,
    *vertWithTri, *triWithVert;
  int ii;

  vertWithTri = AIR_CAST(unsigned int*, nVertWithTri->data);
  triWithVert = AIR_CAST(unsigned int*, nTriWithVert->data);
  maxTriPerVert = nTriWithVert->axis[0].size - 1;
  for (ii=0; ii<3; ii++) {
    vertA = (vertWithTri + 3*triIdx)[ii];
    vertB = (vertWithTri + 3*triIdx)[AIR_MOD(ii+1, 3)];


    intxNum = flipListIntx(intxBuff,
                           triWithVert + (1+maxTriPerVert)*vertA,
                           triWithVert + (1+maxTriPerVert)*vertB);
    if (2 == intxNum) {
      neighIdx = intxBuff[0];
      if (neighIdx == triIdx) {
        neighIdx = intxBuff[1];
      }
      neighGot[ii] = AIR_TRUE;
      neighInfo[ii][0] = neighIdx;
      neighInfo[ii][1] = vertB;
      neighInfo[ii][2] = vertA;
    } else {
      neighGot[ii] = AIR_FALSE;
    }
  }
  return;
}
