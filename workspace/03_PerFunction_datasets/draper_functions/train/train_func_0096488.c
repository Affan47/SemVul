calc_tuple_str_prob (BNTree *bntree, char *tuple, int conditional) {
  int *assignment = malloc (bntree->num_seqs * sizeof(int));
  double result;
  int tuple_idx;
  int i, j;

  if ((int)strlen(tuple) != (bntree->order + 1) * (bntree->num_seqs + 1) - 1) {
    fprintf (stderr, "Wrong length for tuple %s\n", tuple);
    exit (-1);
  }


  for (i=0; i<bntree->num_seqs; i++)
    assignment[i] = 0;

  tuple_idx = 0;
  for (i=bntree->order; i>=0; i--) {
    for (j=0; j<bntree->num_seqs; j++) {
      assignment[j] += intpow (ALPHABET_SIZE, i) * bntree->symbol_map[(int)tuple[tuple_idx]];
      tuple_idx++;
    }
    tuple_idx++;
  }

  result = calc_tuple_prob (bntree, assignment, conditional);
  free (assignment);
  return result;
}
