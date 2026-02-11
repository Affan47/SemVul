split_rtree_node(SplitStruct *node, int n_entries,
                   int all_size,
                   int key_size,
                   int min_size,
                   int size1, int size2 ,
                   double **d_buffer, int n_dim)
{
  SplitStruct *cur;
  SplitStruct *UNINIT_VAR(a), *UNINIT_VAR(b);
  double *g1 = reserve_coords(d_buffer, n_dim);
  double *g2 = reserve_coords(d_buffer, n_dim);
  SplitStruct *UNINIT_VAR(next);
  int UNINIT_VAR(next_node);
  int i;
  SplitStruct *end = node + n_entries;

  if (all_size < min_size * 2)
  {
    return 1;
  }

  cur = node;
  for (; cur<end; ++cur)
  {
    cur->square = count_square(cur->coords, n_dim);
    cur->n_node = 0;
  }

  pick_seeds(node, n_entries, &a, &b, n_dim);
  a->n_node = 1;
  b->n_node = 2;


  copy_coords(g1, a->coords, n_dim);
  size1 += key_size;
  copy_coords(g2, b->coords, n_dim);
  size2 += key_size;


  for (i=n_entries - 2; i>0; --i)
  {
    if (all_size - (size2 + key_size) < min_size)
    {
      mark_all_entries(node, n_entries, 1);
      break;
    }

    if (all_size - (size1 + key_size) < min_size)
    {
      mark_all_entries(node, n_entries, 2);
      break;
    }

    pick_next(node, n_entries, g1, g2, &next, &next_node, n_dim);
    if (next_node == 1)
    {
      size1 += key_size;
      mbr_join(g1, next->coords, n_dim);
    }
    else
    {
      size2 += key_size;
      mbr_join(g2, next->coords, n_dim);
    }
    next->n_node = next_node;
  }

  return 0;
}
