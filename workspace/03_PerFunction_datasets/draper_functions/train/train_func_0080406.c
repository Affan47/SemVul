rdg_build_components (struct graph *rdg, vec<int> starting_vertices,
		      vec<rdgc> *components)
{
  int i, v;
  bitmap saved_components = BITMAP_ALLOC (NULL);
  int n_components = graphds_scc (rdg, NULL);


  typedef vec<int> vec_int_heap;
  vec<int> *all_components = XNEWVEC (vec_int_heap, n_components);

  for (i = 0; i < n_components; i++)
    all_components[i].create (3);

  for (i = 0; i < rdg->n_vertices; i++)
    all_components[rdg->vertices[i].component].safe_push (i);

  FOR_EACH_VEC_ELT (starting_vertices, i, v)
    {
      int c = rdg->vertices[v].component;

      if (bitmap_set_bit (saved_components, c))
	{
	  rdgc x = XCNEW (struct rdg_component);
	  x->num = c;
	  x->vertices = all_components[c];

	  components->safe_push (x);
	}
    }

  for (i = 0; i < n_components; i++)
    if (!bitmap_bit_p (saved_components, i))
      all_components[i].release ();

  free (all_components);
  BITMAP_FREE (saved_components);
}
