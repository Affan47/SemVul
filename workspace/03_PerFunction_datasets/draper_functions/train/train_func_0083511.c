xjumpm_(int *jumpm, int *mult, int *iadd,
	int *irann, int *iranm, int *iam, int *icm) {
  int i__1;

  int i, j[2];

  if (*jumpm > 0) {
	  for (i = 0; i < 2; ++i) {
	    iam[i] = mult[i];
	    icm[i] = iadd[i];
	  }
	  i__1 = *jumpm - 1;
	  for (i = 0; i < i__1; ++i) {
	    PTRANS_lmul( iam, mult, j);
	    iam[0] = j[0];
	    iam[1] = j[1];
	    PTRANS_lmul( icm, mult, j );
	    PTRANS_ladd( iadd, j, icm );
	  }
	  PTRANS_lmul( irann, iam, j );
	  PTRANS_ladd( j, icm, iranm );
  } else {
	  iranm[0] = irann[0];
	  iranm[1] = irann[1];
  }

  return 0;
}
