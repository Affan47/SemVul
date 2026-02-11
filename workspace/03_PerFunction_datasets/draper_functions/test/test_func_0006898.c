dirichlet_boundary(MACRO_DATA *data)
{
  int      i, dim = data->dim;

  if(!data->boundary)
    data->boundary = MEM_ALLOC(data->n_macro_elements*N_NEIGH(dim), S_CHAR);

  for (i = 0; i < data->n_macro_elements * N_NEIGH(dim); i++)
    data->boundary[i] = (data->neigh[i]>=0) ? INTERIOR : DIRICHLET;

  return;
}
