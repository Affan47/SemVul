cluster_is_consistent(GtArray *pgls)
{
  unsigned long i, j, maxright = GT_UNDEF_ULONG, gen_file_num = GT_UNDEF_ULONG;
  GthPGL *pgl;
  bool strandsign = GT_UNDEF_BOOL;
  GthSA *sa;
  GtRange range;

  for (i = 0; i < gt_array_size(pgls); i++) {
    pgl = *(GthPGL**) gt_array_get(pgls, i);

    for (j = 0; j < gt_array_size(pgl->alignments); j++) {
      sa = *(GthSA**) gt_array_get(pgl->alignments, j);
      if (j == 0) {

        gen_file_num = gth_sa_gen_file_num(sa);


        strandsign = gth_sa_gen_strand_forward(sa);


        range = gth_sa_range_forward(sa);
        maxright = range.end;
      }
      else {

        if (gth_sa_gen_file_num(sa) != gen_file_num)
          return false;


        if (gth_sa_gen_strand_forward(sa) != strandsign)
          return false;


        range = gth_sa_range_forward(sa);
        if (range.start > maxright)
          return false;
        if (range.end > maxright)
          maxright = range.end;
      }
    }
  }

  return true;
}
