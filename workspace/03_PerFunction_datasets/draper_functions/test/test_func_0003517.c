gt_style_delete_without_state(GtStyle *sty)
{
  if (!sty) return;
  gt_rwlock_wrlock(sty->lock);
  if (sty->reference_count)
  {
    sty->reference_count--;
    gt_rwlock_unlock(sty->lock);
    return;
  }
  gt_free(sty->filename);
  gt_rwlock_unlock(sty->lock);
  gt_rwlock_delete(sty->lock);
  gt_rwlock_delete(sty->clone_lock);
  gt_free(sty);
}
