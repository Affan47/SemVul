gt_sort_stream_free(GtNodeStream *ns)
{
  unsigned long i;
  GtSortStream *sort_stream = gt_sort_stream_cast(ns);
  for (i = sort_stream->idx; i < gt_array_size(sort_stream->nodes); i++) {
    gt_genome_node_delete(*(GtGenomeNode**)
                          gt_array_get(sort_stream->nodes, i));
  }
  gt_array_delete(sort_stream->nodes);
  gt_node_stream_delete(sort_stream->in_stream);
}
