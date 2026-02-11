gt_diagram_reset_track_selector_func(GtDiagram *diagram)
{
  gt_assert(diagram);
  gt_rwlock_wrlock(diagram->lock);
  diagram->select_func = default_track_selector;
  gt_hashmap_delete(diagram->blocks);
  diagram->blocks = NULL;
  gt_rwlock_unlock(diagram->lock);
}
