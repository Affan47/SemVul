mRNA_set_target_attribute(GtFeatureNode *mRNA_feature,
                                      const GtCSASpliceForm *csa_splice_form)
{
  unsigned long i;
  GtStr *targets;
  gt_assert(mRNA_feature && csa_splice_form);
  targets = gt_str_new();
  for (i = 0; i < gt_csa_splice_form_num_of_sas(csa_splice_form); i++) {
    GtFeatureNode *sa = *(GtFeatureNode**)
                        gt_csa_splice_form_get_sa(csa_splice_form, i);
    if (gt_feature_node_get_attribute(sa, GT_GFF_TARGET)) {
      if (gt_str_length(targets))
        gt_str_append_char(targets, ',');
      gt_str_append_cstr(targets,
                         gt_feature_node_get_attribute(sa, GT_GFF_TARGET));
    }
  }
  if (gt_str_length(targets)) {
    gt_feature_node_add_attribute(mRNA_feature, GT_GFF_TARGET,
                                  gt_str_get(targets));
  }
  gt_str_delete(targets);
}
