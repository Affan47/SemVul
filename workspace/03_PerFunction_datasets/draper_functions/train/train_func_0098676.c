jerasure_bitmatrix_decode(int k, int m, int w, int *bitmatrix, int row_k_ones, int *erasures,
                            char **data_ptrs, char **coding_ptrs, int size, int packetsize)
{
  int i;
  int *erased;
  int *decoding_matrix;
  int *dm_ids;
  int edd, *tmpids, lastdrive;

  erased = jerasure_erasures_to_erased(k, m, erasures);
  if (erased == NULL) return -1;


  lastdrive = k;

  edd = 0;
  for (i = 0; i < k; i++) {
    if (erased[i]) {
      edd++;
      lastdrive = i;
    }
  }

  if (row_k_ones != 1 || erased[k]) lastdrive = k;

  dm_ids = NULL;
  decoding_matrix = NULL;

  if (edd > 1 || (edd > 0 && (row_k_ones != 1 || erased[k]))) {

    dm_ids = talloc(int, k);
    if (dm_ids == NULL) {
      free(erased);
      return -1;
    }

    decoding_matrix = talloc(int, k*k*w*w);
    if (decoding_matrix == NULL) {
      free(erased);
      free(dm_ids);
      return -1;
    }

    if (jerasure_make_decoding_bitmatrix(k, m, w, bitmatrix, erased, decoding_matrix, dm_ids) < 0) {
      free(erased);
      free(dm_ids);
      free(decoding_matrix);
      return -1;
    }
  }

  for (i = 0; edd > 0 && i < lastdrive; i++) {
    if (erased[i]) {
      jerasure_bitmatrix_dotprod(k, w, decoding_matrix+i*k*w*w, dm_ids, i, data_ptrs, coding_ptrs, size, packetsize);
      edd--;
    }
  }

  if (edd > 0) {
    tmpids = talloc(int, k);
    for (i = 0; i < k; i++) {
      tmpids[i] = (i < lastdrive) ? i : i+1;
    }
    jerasure_bitmatrix_dotprod(k, w, bitmatrix, tmpids, lastdrive, data_ptrs, coding_ptrs, size, packetsize);
    free(tmpids);
  }

  for (i = 0; i < m; i++) {
    if (erased[k+i]) {
      jerasure_bitmatrix_dotprod(k, w, bitmatrix+i*k*w*w, NULL, k+i, data_ptrs, coding_ptrs, size, packetsize);
    }
  }

  free(erased);
  if (dm_ids != NULL) free(dm_ids);
  if (decoding_matrix != NULL) free(decoding_matrix);

  return 0;
}
