_dxfRemoveEdgesFromHeap(int *estar, u_short val, int *edge2index,
			    SimpData *simp_data)
{
  int
    num_removed = 0;

  register u_short i;


  for(i=0;i<val;i++)
    {
      int the_edge = estar[i];
      int idx      = edge2index[the_edge];
      num_removed += simp_data->remove_edge(simp_data, idx, the_edge);
    }

  return num_removed;
}
