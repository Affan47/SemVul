calculateML (INFO *info) {
  unsigned int num_clusters = info -> num_clusters;
  register unsigned int i;
  register unsigned int j;
  register unsigned int k;
  register unsigned int pos_j;
  register unsigned int cos_count;
  register PROBNODE total = 0.0;
  PROBNODE temp;
  unsigned int count = 0;
  time_t start;
  time_t end;

  time (&start);

  for (i = 0; i < info -> m; i++) {
    cos_count = GET_COS_POSITION (i, 0);
    for (pos_j = 1; pos_j <= cos_count; pos_j++) {
      j = GET_COS_POSITION (i, pos_j);


      temp = (GET_PROBZ (0) + GET_PROBW1_Z (0, i) + GET_PROBW2_Z (0, j));

      for (k = 1; k < num_clusters; k++) {

        logSumsInline (temp, GET_PROBZ (k) + GET_PROBW1_Z (k, i) + GET_PROBW2_Z (k, j));
      }


      total += (temp * DOEXP (GET_COS (i, pos_j)));
      count++;
    }
  }

  time (&end);
  info -> calculateML_time += difftime (end, start);

  return (total);
}
