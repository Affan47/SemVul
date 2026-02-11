annotate_nodes(GtArray *candidates, GtArray *groups,
                          const char *famprefix, GtError *err)
{
  GtArray *group_member;
  GtBittab *group;
  GtFeatureNode *curnode;
  GtFeatureNodeIterator *fni = NULL;
  GtGenomeNode *gn;
  int had_err = 0;
  unsigned long i, j, index, famno = 0;

  gt_assert(candidates && groups);
  gt_error_check(err);

  for (i = 0; i < gt_array_size(groups); i++) {
    group = *(GtBittab**) gt_array_get(groups, i);
    group_member = gt_array_new(sizeof(unsigned long));
    gt_bittab_get_all_bitnums(group, group_member);
    if (gt_array_size(group_member) < 2UL) {
      gt_array_delete(group_member);
      continue;
    }
    for (j = 0; j < gt_array_size(group_member); j++) {
      index = *(unsigned long*) gt_array_get(group_member, j);
      gn = *(GtGenomeNode**) gt_array_get(candidates, index);
      fni = gt_feature_node_iterator_new((GtFeatureNode*) gn);
      curnode = gt_feature_node_iterator_next(fni);
      if (strcmp(gt_feature_node_get_type(curnode), gt_ft_repeat_region) == 0) {
        char fam[BUFSIZ];
        if (famprefix != NULL)
          (void) snprintf(fam, BUFSIZ, "%s%lu", famprefix, famno);
        else
          (void) snprintf(fam, BUFSIZ, "ltrfam_%lu", famno);
        gt_feature_node_set_attribute(curnode, "ltrfam", fam);
      } else {
        gt_feature_node_iterator_delete(fni);
        gt_error_set(err, "repeat_region is not root node");
        had_err = -1;
        break;
      }
      gt_feature_node_iterator_delete(fni);
    }
    gt_array_delete(group_member);
    if (had_err)
      break;
    famno++;
  }
  return had_err;
}
