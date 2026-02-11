gt_orphanage_get_orphan(GtOrphanage *o)
{
  gt_assert(o);
  if (gt_queue_size(o->orphans))
    return gt_queue_get(o->orphans);
  return NULL;
}
