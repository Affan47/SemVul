check_fct(const EL_INFO *el_info, void *data)
{
  FUNCNAME("check_fct");
  CHECK_TRAVERSE_DATA *ud = (CHECK_TRAVERSE_DATA *)data;
  MESH                *mesh = el_info->mesh;
  int                  i, j, k, opp_v = -1;
  int                  dim = el_info->mesh->dim;
  EL                  *el, *neigh;

  TEST_FLAG(FILL_NEIGH, el_info);

  el = el_info->el;
  for (i = 0; i < N_NEIGH(dim); i++)
  {
    if ((neigh = el_info->neigh[i]))
    {
      if (((dim == 1) && el_info->vertex_bound[1-i])
#if DIM_OF_WORLD > 1
	  || ((dim == 2) && el_info->edge_bound[i])
#if DIM_OF_WORLD > 2
	  || ((dim == 3) && el_info->face_bound[i])
#endif
#endif
	  ) {
	if (!ud->error_detected)
	  MSG("error detected!!!\n");
	ud->error_detected++;
	MSG("interior boundary to neighbor %d nonzero on element = %d\n",
	    i, INDEX(el));
      }

      if (dim > 0) {
	opp_v = el_info->opp_vertex[i];
	if(opp_v < 0  ||  opp_v >= N_NEIGH(dim))
	  {
	    if (!ud->error_detected)
	      MSG("error detected!!!\n");
	    ud->error_detected++;
	    MSG("opp_v = %d\n", opp_v);
	  }
      }

      if(mesh->n_dof[VERTEX]) {
	for (j = 1; j < N_VERTICES(dim); j++) {
	  for (k = 1; k < N_VERTICES(dim); k++)
	    if (el->dof[(i+j)%(dim+1)] == neigh->dof[(opp_v+k)%(dim+1)]) break;

	  if (k >= N_VERTICES(dim)) {
	    if (!ud->error_detected)
	      MSG("error detected!!!\n");
	    ud->error_detected++;
	    MSG("dof %d of el %d at face %d isn't dof of neigh %d at face %d\n",
		el->dof[(i+j)%(dim+1)][0], INDEX(el), i, INDEX(neigh), opp_v);
	  }
	}
      }
    }
    else
    {
      if ((dim == 1 && !el_info->vertex_bound[1-i])
#if DIM_OF_WORLD > 1
	  || (dim == 2 && !el_info->edge_bound[i])
#if DIM_OF_WORLD > 2
	  || (dim == 3 && !el_info->face_bound[i])
#endif
#endif
	  ) {
	if (!ud->error_detected)
	  MSG("error detected!!!\n");
	ud->error_detected++;
	MSG("boundary to neigh %d on domains boundary is zero on element %d\n",
	    i, INDEX(el));
      }
    }
  }

  return;
}
