remove_preds_and_fake_succs (constraint_graph_t graph)
{
  unsigned int i;


  for (i = 0; i < FIRST_REF_NODE; i++)
    {
      if (graph->succs[i])
	bitmap_clear_range (graph->succs[i], FIRST_REF_NODE,
			    FIRST_REF_NODE * 2);
    }


  for (i = FIRST_REF_NODE; i < graph->size; i++)
    {
      if (graph->succs[i])
	BITMAP_FREE (graph->succs[i]);
    }


  graph->size = VEC_length (varinfo_t, varmap);
  graph->succs = XRESIZEVEC (bitmap, graph->succs, graph->size);

  free (graph->implicit_preds);
  graph->implicit_preds = NULL;
  free (graph->preds);
  graph->preds = NULL;
  bitmap_obstack_release (&predbitmap_obstack);
}
