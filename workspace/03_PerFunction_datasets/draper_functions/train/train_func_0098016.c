cm_MeanMatchRelativeEntropyHMM(const CM_t *cm)
{
  int    v;
  double KL = 0.;
  float left_e[cm->abc->K];
  float right_e[cm->abc->K];
  int i,j;

  for (v = 0; v < cm->M; v++) {
      if(cm->stid[v] == MATP_MP) {


	esl_vec_FSet(left_e, cm->abc->K, 0.);
	for(i = 0; i < cm->abc->K; i++) {
	  for(j = (i*cm->abc->K); j < ((i+1)*cm->abc->K); j++) {
	    left_e[i] += cm->e[v][j];
	  }
	}
	esl_vec_FNorm(left_e, cm->abc->K);
	KL += esl_vec_FRelEntropy(left_e, cm->null, cm->abc->K);


	esl_vec_FSet(right_e, cm->abc->K, 0.);
	for(i = 0; i < cm->abc->K; i++) {
	  for(j = i; j < cm->abc->K * cm->abc->K; j += cm->abc->K) {
	    right_e[i] += cm->e[v][j];
	  }
	}
	KL += esl_vec_FRelEntropy(right_e, cm->null, cm->abc->K);

      }
      else if(cm->stid[v] == MATL_ML ||
	      cm->stid[v] == MATR_MR) {
	KL += esl_vec_FRelEntropy(cm->e[v], cm->null, cm->abc->K);

      }
  }

  KL /= (double) cm->clen;
  return KL;
}
