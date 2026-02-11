determine_transcripttypes(GtFeatureNode *fn, void *data,
                                     GT_UNUSED GtError *err)
{
  SaveExonAndCDSInfo *info = (SaveExonAndCDSInfo*) data;
  GT_UNUSED int had_err;
  gt_error_check(err);
  gt_assert(fn && info);

  gt_array_reset(info->exon_features);
  gt_array_reset(info->cds_features);

  had_err = gt_feature_node_traverse_direct_children(fn, info,
                                                     save_exons_and_cds, NULL);
  gt_assert(!had_err);

  set_transcript_types(info->exon_features, gt_feature_node_get_strand(fn));
  set_transcript_types(info->cds_features, gt_feature_node_get_strand(fn));
  return 0;
}
