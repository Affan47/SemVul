compute_sam_flag_nomate (int pathnum, int npaths, bool firstp, bool watsonp, bool sam_paired_p) {
  unsigned int flag = 0U;

  if (sam_paired_p == true) {
    flag |= PAIRED_READ;
    if (firstp == true) {
      flag |= FIRST_READ_P;
    } else {
      flag |= SECOND_READ_P;
    }
  }

  if (npaths == 0) {
    flag |= QUERY_UNMAPPED;
  } else if (watsonp == false) {
    flag |= QUERY_MINUSP;
  }

#if 0

  if (pathnum > 1) {
    flag |= NOT_PRIMARY;
  }
#endif

  return flag;
}
