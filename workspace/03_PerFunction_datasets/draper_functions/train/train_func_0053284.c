gt_feature_index_get_range_for_seqid(GtFeatureIndex *feature_index,
                                          GtRange *range,
                                          const char *seqid,
                                          GtError *err)
{
  int ret;
  gt_assert(feature_index && feature_index->c_class && range && seqid);
  gt_rwlock_rdlock(feature_index->pvt->lock);
  ret = feature_index->c_class->get_range_for_seqid(feature_index, range,
                                                    seqid, err);
  gt_rwlock_unlock(feature_index->pvt->lock);
  return ret;
}
