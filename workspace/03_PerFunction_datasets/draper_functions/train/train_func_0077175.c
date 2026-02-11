_dxfCollapseBoundaryEdge2ndKnd(SimpData *simp_data,
				   int edg_num, int v0, int v1, int val0, int val1,
				   int *star0, int *star1, int *vstar0, int *vstar1, int *estar0, int *estar1,
				   Vertex *s_normal0, Vertex *s_normal1, float *s_area0, float *s_area1)
{
  int
    n_edges_added[2],
    n_edges_reinstated = 0;


  simp_data->vertex_father[v1]         = v0;

  if (val1 > 1)
    {
      simp_data->edge_father   [estar1[0]] = simp_data->edge_father   [estar0[0]];

      simp_data->triangle_father[star1[0]] = simp_data->triangle_father[star1[1]];
    }
  else
    {
      simp_data->edge_father   [estar0[0]] = simp_data->edge_father   [estar1[0]];

      simp_data->triangle_father[star0[0]] = simp_data->triangle_father[star0[1]];
    }


  simp_data->valence[v0]               = val0 + val1 - 2;
  simp_data->valence[vstar0[0]] --;


  _dxfRemoveEdgesFromHeap(estar0, val0, simp_data->edge2index, simp_data);

  _dxfRemoveEdgesFromHeap(estar1, val1, simp_data->edge2index, simp_data);


  if (simp_data->edge2index[estar1[0]] != simp_data->heap_outside_index)
    simp_data->num_edg_remaining_4_testing --;

  simp_data->edge2index[estar1[0]] = -4;
  simp_data->edge2index[edg_num]   = -7;


  n_edges_reinstated =
    _dxfReinstateEdgesInHeap(estar0, val0, simp_data, n_edges_added);


  n_edges_reinstated +=
    _dxfReinstateEdgesInHeap(estar1+1, val1-1, simp_data, n_edges_added+1);


  simp_data->num_edg_remaining_4_testing += n_edges_reinstated;


  memcpy(simp_data->vert[v0], simp_data->simplified_vertex, sizeof(Vertex));


  {
    register int i;

    float
      *s_comp0 = s_area0 + val0,
      *s_comp1 = s_area1 + val1;


    for(i=1;i<val0;i++)
      {
	simp_data->area[star0[i]]         = s_area0[i];
	simp_data->compactness[star0[i]]  = s_comp0[i];
	memcpy(simp_data->normal[star0[i]], s_normal0[i], sizeof(Vertex));
      }


    for(i=1;i<val1;i++)
      {
	simp_data->area[star1[i]]         = s_area1[i];
	simp_data->compactness[star1[i]]  = s_comp1[i];
	memcpy(simp_data->normal[star1[i]], s_normal1[i], sizeof(Vertex));
      }
  }


  return n_edges_added[0] + n_edges_added[1];
}
