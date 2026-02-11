smartlist_pqueue_remove(smartlist_t *sl,
                        int (*compare)(const void *a, const void *b),
                        int idx_field_offset,
                        void *item)
{
  int idx = IDX_OF_ITEM(item);
  tor_assert(idx >= 0);
  tor_assert(sl->list[idx] == item);
  --sl->num_used;
  *IDXP(item) = -1;
  if (idx == sl->num_used) {
    return;
  } else {
    sl->list[idx] = sl->list[sl->num_used];
    UPDATE_IDX(idx);
    smartlist_heapify(sl, compare, idx_field_offset, idx);
  }
}
