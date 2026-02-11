positive_matrix(pssm, matrix)
     struct work_pssm *pssm;
     Matrix *matrix;
{
  int pos, aa;
  double factor, maxval, minval, dtemp;

  minval = 9999.9;
  maxval = -9999.9;
  for (pos = 0; pos < matrix->width; pos++) {
    for (aa=1; aa < AAS; aa++) {
      if (pssm->value[pos][aa] < minval) minval = pssm->value[pos][aa];
      if (pssm->value[pos][aa] > maxval) maxval = pssm->value[pos][aa];
    }
  }

  if (minval < 0.0) {
    factor = 99.0 / (maxval - minval);
  }
  else {
    factor = 99.0 / maxval;
  }
  if (factor < 1.0) {
    factor = 1.0;
  }
  for (pos = 0; pos < matrix->width; pos++) {
    for (aa=1; aa < AAS; aa++) {
      if (minval < 0.0) {
	dtemp = factor * (pssm->value[pos][aa] - minval);
      }
      else {
	dtemp = factor * pssm->value[pos][aa];
      }
      matrix->weights[aa][pos] = (MatType) dtemp;
    }
    compute_BZX(matrix, pos);
  }
}
