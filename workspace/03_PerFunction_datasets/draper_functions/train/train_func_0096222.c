orf_attach_results_to_gff3(GtFeatureNode *gf,
                                       GtRange orf_rng, unsigned int orf_frame,
                                       GtStrand strand, GT_UNUSED GtError *err)
{
  GtGenomeNode *child;
  GtStr *tag;
  tag = gt_str_new_cstr(GT_ORF_FINDER_TAG);

  orf_rng.start++; orf_rng.end++;

  GtFeatureNodeIterator *gfi;
  GtFeatureNode *curnode = NULL, *parent_node = NULL;
  GtRange gfi_range;
  char frame_buf[3];
  sprintf(frame_buf, "%d", orf_frame);

  gfi = gt_feature_node_iterator_new(gf);

  while ((curnode = gt_feature_node_iterator_next(gfi))) {
    if (strcmp(gt_feature_node_get_type(curnode),
                                              (const char*) GT_ORF_TYPE) != 0) {
      gfi_range = gt_genome_node_get_range((GtGenomeNode*) curnode);
      if (gt_range_contains(&gfi_range, &orf_rng)) {
        parent_node = curnode;
      }
    }
  }
  if (parent_node) {
    child = gt_feature_node_new(gt_genome_node_get_seqid((GtGenomeNode*) gf),
                                GT_ORF_TYPE,
                                orf_rng.start,
                                orf_rng.end,
                                strand);
    gt_feature_node_set_source((GtFeatureNode*) child, tag);
    gt_feature_node_set_attribute((GtFeatureNode*) child, "frame", frame_buf);
    gt_feature_node_add_child(parent_node,(GtFeatureNode*) child);
  }
  gt_str_delete(tag);
  gt_feature_node_iterator_delete(gfi);
}
