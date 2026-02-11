rdg_build_components (struct graph *rdg, VEC (int, heap) *starting_vertices,
		      VEC (rdgc, heap) **components)
{
  int i, v;
  bitmap saved_components = BITMAP_ALLOC (NULL);
  int n_components = graphds_scc (rdg, NULL);
  VEC (int, heap) **all_components = XNEWVEC (VEC (int, heap) *, n_components);

  for (i = 0; i < n_components; i++)
    all_components[i] = VEC_alloc (int, heap, 3);

  for (i = 0; i < rdg->n_vertices; i++)
    VEC_safe_push (int, heap, all_components[rdg->vertices[i].component], i);

  FOR_EACH_VEC_ELT (int, starting_vertices, i, v)
    {
      int c = rdg->vertices[v].component;

      if (bitmap_set_bit (saved_components, c))
	{
	  rdgc x = XCNEW (struct rdg_component);
	  x->num = c;
	  x->vertices = all_components[c];

	  VEC_safe_push (rdgc, heap, *components, x);
	}
    }

  for (i = 0; i < n_components; i++)
    if (!bitmap_bit_p (saved_components, i))
      VEC_free (int, heap, all_components[i]);

  free (all_components);
  BITMAP_FREE (saved_components);
}
