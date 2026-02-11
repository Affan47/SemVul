node_attribute_change_callback(GtFeatureNode *changed,
                                           GT_UNUSED bool added,
                                           GT_UNUSED const char *key,
                                           GT_UNUSED const char *value,
                                           void *data)
{
  unsigned long *id;
  ObserverCallbackInfo *info = (ObserverCallbackInfo*) data;
  gt_assert(changed);
  if ((id = node_ul_gt_hashmap_get(info->fis->cache_node2id, changed))) {
    gt_hashmap_add(info->fis->changed, changed, (void*) 1);
  }
}
