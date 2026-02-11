ladish_graph_destroy(ladish_graph_handle graph_handle)
{
  ladish_graph_clear(graph_handle, NULL);
  ladish_dict_destroy(graph_ptr->dict);
  if (graph_ptr->opath != NULL)
  {
    free(graph_ptr->opath);
  }
  free(graph_ptr);
}
