create_CDS_features_for_longest_ORF(GtArray *orfs, GtCDSVisitor *v,
                                                GtFeatureNode *fn)
{
  if (gt_array_size(orfs)) {

    gt_ranges_sort_by_length_stable(orfs);


    if (gt_range_length(gt_array_get_first(orfs)) >=
        v->minorflen * GT_CODON_LENGTH) {
      create_CDS_features_for_ORF(*(GtRange*) gt_array_get_first(orfs), v, fn);
    }
  }
}
