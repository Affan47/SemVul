get_min_alpha_beta_sum (fullmat_t *fullmat) {
  float max_sum = 9999999.9;
  float cur_dif;
  int i,j,k,l;
  int pair_ij, pair_kl;

  for (i=0; i<fullmat->abc->K; i++)
    for (j=0; j<fullmat->abc->K; j++)
      for (k=0; k<fullmat->abc->K; k++)
	for (l=0; l<fullmat->abc->K; l++) {
	  pair_ij = numbered_basepair(fullmat->abc->sym[i], fullmat->abc->sym[j]);
	  pair_kl = numbered_basepair(fullmat->abc->sym[k], fullmat->abc->sym[l]);

	  cur_dif = fullmat->paired->matrix[matrix_index(pair_ij, pair_kl)] -
	    fullmat->unpaired->matrix[matrix_index(i,k)];
	  if (cur_dif < max_sum)
	    max_sum = cur_dif;

	  cur_dif = fullmat->paired->matrix[matrix_index(pair_ij, pair_kl)] -
	    fullmat->unpaired->matrix[matrix_index(j,l)];
	  if (cur_dif < max_sum)
	    max_sum = cur_dif;
	}
  return (-1. * max_sum);
}
