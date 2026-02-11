tnsCount(TNS_INFO *tnsInfo, Word16 blockType)
{

  Word32 i, k;
  Flag tnsPresent;
  Word32 numOfWindows;
  Word32 count;
  Word32 coefBits;
  Word16 *ptcoef;

  count = 0;

  if (blockType == 2)
    numOfWindows = 8;
  else
    numOfWindows = 1;
  tnsPresent = 0;

  for (i=0; i<numOfWindows; i++) {

    if (tnsInfo->tnsActive[i]!=0) {
      tnsPresent = 1;
    }
  }

  if (tnsPresent) {


    for (i=0; i<numOfWindows; i++) {

      if (blockType == 2)
        count += 1;
      else
        count += 2;

      if (tnsInfo->tnsActive[i]) {
        count += 1;

        if (blockType == 2) {
          count += 4;
          count += 3;
        }
        else {
          count += 6;
          count += 5;
        }

        if (tnsInfo->order[i]) {
          count += 1;
          count += 1;

          if (tnsInfo->coefRes[i] == 4) {
            ptcoef = tnsInfo->coef + i*TNS_MAX_ORDER_SHORT;
			coefBits = 3;
            for(k=0; k<tnsInfo->order[i]; k++) {

              if ((ptcoef[k] > 3) || (ptcoef[k] < -4)) {
                coefBits = 4;
                break;
              }
            }
          }
          else {
            coefBits = 2;
            ptcoef = tnsInfo->coef + i*TNS_MAX_ORDER_SHORT;
			for(k=0; k<tnsInfo->order[i]; k++) {

              if ((ptcoef[k] > 1) || (ptcoef[k] < -2)) {
                coefBits = 3;
                break;
              }
            }
          }
          for (k=0; k<tnsInfo->order[i]; k++ ) {
            count += coefBits;
          }
        }
      }
    }
  }

  return count;
}
