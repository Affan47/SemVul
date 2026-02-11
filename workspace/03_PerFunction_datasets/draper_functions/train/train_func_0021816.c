sort_iter_single(long num_links, double *restrict add1, int parent)
{


  static int MERGE_SORT_LIMIT_SIZE = 16384;
  static int first_sort_iter_call = 1;
  static double merge_time;

  int par_depth = 1;

  if ( first_sort_iter_call )
    {
      first_sort_iter_call = 0;
      par_depth = (int)(log(parent)/log(2));
      MERGE_SORT_LIMIT_SIZE = num_links/parent/2 ;
      if ( MERGE_SORT_LIMIT_SIZE < 4096 ) MERGE_SORT_LIMIT_SIZE = 4096;
      parent = 1;
    }

  if ( num_links > MERGE_SORT_LIMIT_SIZE )
    sort_par(num_links, add1, parent, par_depth);
  else
    sort_add(num_links,add1);

  if ( parent == 1 ) {
    first_sort_iter_call = 1;


    merge_time = 0;
  }

  return;
}
