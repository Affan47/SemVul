tidy_region_node_visitor_region_node(GtNodeVisitor *nv,
                                                GtRegionNode *rn,
                                                GT_UNUSED GtError *err)
{
  GtTidyRegionNodeVisitor *trnv;
  const char *seqid;
  gt_error_check(err);
  trnv = tidy_region_node_visitor_cast(nv);
  seqid = gt_str_get(gt_genome_node_get_seqid((GtGenomeNode*) rn));
  gt_assert(seqid);
  if (!gt_hashmap_get(trnv->region_nodes, seqid)) {
    gt_hashmap_add(trnv->region_nodes, gt_cstr_dup(seqid),
                   gt_genome_node_ref((GtGenomeNode*) rn));
    gt_assert(gt_hashmap_get(trnv->region_nodes, seqid));
  }
  gt_queue_add(trnv->node_buffer, rn);
  return 0;
}
