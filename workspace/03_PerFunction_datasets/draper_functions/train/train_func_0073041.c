art_svp_render_insert_active (int i, int *active_segs, int n_active_segs,
			      artfloat *seg_x, artfloat *seg_dx)
{
  int j;
  artfloat x;
  int tmp1, tmp2;


  x = seg_x[i] + 0.001 * seg_dx[i];
  for (j = 0; j < n_active_segs && seg_x[active_segs[j]] < x; j++);

  tmp1 = i;
  while (j < n_active_segs)
    {
      tmp2 = active_segs[j];
      active_segs[j] = tmp1;
      tmp1 = tmp2;
      j++;
    }
  active_segs[j] = tmp1;
}
