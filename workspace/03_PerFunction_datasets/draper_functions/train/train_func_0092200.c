gt_ma_clean(void)
{
  gt_assert(ma);
  gt_rwlock_wrlock(ma->bookkeeping_lock);
  ma->bookkeeping = false;
  gt_hashmap_delete(ma->allocated_pointer);
  gt_rwlock_unlock(ma->bookkeeping_lock);
  gt_rwlock_delete(ma->bookkeeping_lock);
  free(ma);
  ma = NULL;
}
