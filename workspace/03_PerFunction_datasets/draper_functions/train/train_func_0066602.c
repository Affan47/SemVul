gt_ltr_cluster_stream_free(GtNodeStream *ns)
{
  unsigned long i;
  GtLTRClusterStream *lcs = gt_ltr_cluster_stream_cast(ns);
  gt_node_visitor_delete((GtNodeVisitor*) lcs->lcv);
  gt_hashmap_delete(lcs->feat_to_encseq);
  gt_str_array_delete(lcs->feat_to_encseq_keys);
  for (i = 0; i < gt_array_size(lcs->nodes); i++)
    gt_genome_node_delete(*(GtGenomeNode**) gt_array_get(lcs->nodes, i));
  gt_array_delete(lcs->nodes);
  gt_node_stream_delete(lcs->in_stream);
}
