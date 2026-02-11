ggc_prune_ptr (void **slot, void *b ATTRIBUTE_UNUSED)
{
  struct ptr_hash_entry *p = (struct ptr_hash_entry *) *slot;
  if (!ggc_marked_p (p->ptr))
    {
      p->loc->collected += p->size;
      htab_clear_slot (ptr_hash, slot);
      free (p);
    }
  return 1;
}
