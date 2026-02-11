free_rdg (struct graph *rdg)
{
  int i;

  for (i = 0; i < rdg->n_vertices; i++)
    {
      struct vertex *v = &(rdg->vertices[i]);
      struct graph_edge *e;

      for (e = v->succ; e; e = e->succ_next)
	if (e->data)
	  free (e->data);

      if (v->data)
	free (v->data);
    }

  htab_delete (rdg->indices);
  free_graph (rdg);
}
