gt_orf_finder_visitor_feature_node(GtNodeVisitor *gv,
                                             GtFeatureNode *gf,
                                             GtError *err)
{
  GtORFFinderVisitor *lv;
  const char *gft = NULL;
  GtFeatureNodeIterator *gfi;
  GtFeatureNode *curnode = NULL;
  int had_err = 0;
  unsigned long seqnum = GT_UNDEF_ULONG;
  GtRange rng;

  lv = gt_orf_finder_visitor_cast(gv);
  gt_assert(lv);
  gt_error_check(err);

  gfi = gt_feature_node_iterator_new(gf);

  while (!had_err && (curnode = gt_feature_node_iterator_next(gfi))) {
    gft = gt_feature_node_get_type(curnode);

    if (gt_hashmap_get(lv->types, (void*) gft) != NULL ||
                       gt_hashmap_get(lv->types,
                                      (void*) "all") == (void*) 1) {
      GtStr *val;
      val = gt_genome_node_get_seqid((GtGenomeNode*) curnode);
      if (val == NULL) {
        gt_error_set(err, "missing attribute \"seq_number\"");
        had_err = -1;
      }
      if (sscanf(gt_str_get(val), "seq%lu", &seqnum) != 1) {
        had_err = -1;
      }
      gt_assert(seqnum != GT_UNDEF_ULONG);
      if (!had_err) {
        rng = gt_genome_node_get_range((GtGenomeNode*) curnode);
        had_err = run_orffinder(lv->encseq, curnode, rng.start - 1, rng.end - 1,
                                seqnum, lv->min, lv->max, lv->all, err);
        if (gt_hashmap_get(lv->types,
                           (void*) "all") == (void*) 1) {
          break;
        }
        else if (gt_feature_node_has_children(curnode)) {
          GtFeatureNode *tmpnode = NULL;
          GtFeatureNodeIterator *tmpgfi = gt_feature_node_iterator_new(curnode);
          tmpnode = gt_feature_node_iterator_next(tmpgfi);
          while ((tmpnode = gt_feature_node_iterator_next(tmpgfi))) {
            gft = gt_feature_node_get_type(tmpnode);
            if (strcmp(gft, (const char*) GT_ORF_TYPE) == 0) {
              continue;
            }
            curnode = gt_feature_node_iterator_next(gfi);
          }
          gt_feature_node_iterator_delete(tmpgfi);
        }
      }
    }
  }

  gt_feature_node_iterator_delete(gfi);

  return had_err;
}
