gt_diagram_get_range(const GtDiagram *diagram)
{
  GtRange rng;
  gt_assert(diagram);
  gt_rwlock_rdlock(diagram->lock);
  rng = diagram->range;
  gt_rwlock_unlock(diagram->lock);
  return rng;
}
