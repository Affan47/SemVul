gt_feature_index_memory_has_seqid(const GtFeatureIndex *gfi,
                                      bool *has_seqid,
                                      const char *seqid,
                                      GT_UNUSED GtError *err)
{
  GtFeatureIndexMemory *fi;
  gt_assert(gfi);

  fi = gt_feature_index_memory_cast((GtFeatureIndex*) gfi);
  *has_seqid = (gt_hashmap_get(fi->regions, seqid) != NULL);
  return 0;
}
