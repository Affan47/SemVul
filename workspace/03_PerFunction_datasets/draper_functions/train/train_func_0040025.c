p7_Seq2Bands(CM_t *cm, char *errbuf, P7_PROFILE *gm, P7_GMX *gx, P7_BG *bg, P7_TRACE *p7_tr, ESL_DSQ *dsq, int L,
	     double **phi, float sc7, int len7, int end7, float mprob7, float mcprob7, float iprob7, float ilprob7, int pad7,
	     int **ret_i2k, int **ret_kmin, int **ret_kmax, int *ret_ncells)
{
  int   status;
  float usc, nullsc;
  int *k2i, *i2k;
  float *isc;
  int *iconflict;
  int *kmin, *kmax;
  int ncells;


  p7_bg_SetLength(bg, L);
  p7_bg_NullOne(bg, dsq, L, &nullsc);


  p7_gmx_GrowTo(gx, cm->mlp7->M, L);
  p7_ReconfigLength(gm, L);
  gx->M = cm->mlp7->M;
  gx->L = L;


  p7_GMSV(dsq, L, gm, gx, 2.0, &usc);


  status = my_p7_GTraceMSV(dsq, L, gm, gx, p7_tr, &i2k, &k2i, &isc, &iconflict);


  if(status == eslOK) {
    prune_i2k(i2k, iconflict, isc, L, phi, sc7, len7, end7, mprob7, mcprob7, iprob7, ilprob7);
  }
  else if (status == eslEINCOMPAT) {
    esl_vec_ISet(k2i, (cm->mlp7->M+1), -1);
    esl_vec_ISet(i2k, (L+1), -1);
    return status;
  }


  if((status = p7_pins2bands(i2k, errbuf, L, cm->clen, pad7, &kmin, &kmax, &ncells)) != eslOK) return status;


  *ret_i2k  = i2k;
  *ret_kmin = kmin;
  *ret_kmax = kmax;
  *ret_ncells = ncells;

  free(iconflict);
  free(isc);
  free(k2i);

  return eslOK;
}
