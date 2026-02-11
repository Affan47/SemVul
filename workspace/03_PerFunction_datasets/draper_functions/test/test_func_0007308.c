gt_feature_index_memory_get_first_seqid(const GtFeatureIndex *gfi,
                                              GT_UNUSED GtError *err)
{
  GtFeatureIndexMemory *fi;
  gt_assert(gfi);

  fi = gt_feature_index_memory_cast((GtFeatureIndex*) gfi);
  return fi->firstseqid ? gt_cstr_dup(fi->firstseqid) : NULL;
}
