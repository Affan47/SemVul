find_best_endpoint_to_queryend_indels (int *finalscore, int *bestr, int *bestc, struct Int3_T **matrix,
				       int length1, int length2, int extraband_end_or_paired,
				       bool jump_late_p) {
  int bestscore = NEG_INFINITY;
  int r, c;
  int rband, lband, clo, chigh;


  if (length2 >= length1) {

    rband = length2 - length1 + extraband_end_or_paired;
    lband = extraband_end_or_paired;
  } else {

    lband = length1 - length2 + extraband_end_or_paired;
    rband = extraband_end_or_paired;
  }

  *bestr = r = length1;
  *bestc = 0;

  if (jump_late_p == false) {
    if ((clo = r - lband) < 1) {
      clo = 1;
    }
    if ((chigh = r + rband) > length2) {
      chigh = length2;
    }
    if (clo <= chigh) {
      for (c = clo; c <= chigh; c++) {

	if (matrix[r][c].nogap > bestscore) {
	  *bestr = r;
	  *bestc = c;
	  bestscore = matrix[r][c].nogap;
	}
      }
    }

  } else {
    if ((clo = r - lband) < 1) {
      clo = 1;
    }
    if ((chigh = r + rband) > length2) {
      chigh = length2;
    }
    if (clo <= chigh) {
      for (c = clo; c <= chigh; c++) {

	if (matrix[r][c].nogap >= bestscore) {
	  *bestr = r;
	  *bestc = c;
	  bestscore = matrix[r][c].nogap;
	}
      }
    }
  }

  *finalscore = bestscore;
  return;
}
