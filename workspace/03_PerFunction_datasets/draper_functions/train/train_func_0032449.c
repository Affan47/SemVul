copy_reference (vn_reference_t oref, vn_tables_t info)
{
  vn_reference_t ref;
  void **slot;
  ref = (vn_reference_t) pool_alloc (info->references_pool);
  memcpy (ref, oref, sizeof (*ref));
  oref->operands = NULL;
  slot = htab_find_slot_with_hash (info->references, ref, ref->hashcode,
				   INSERT);
  if (*slot)
    free_reference (*slot);
  *slot = ref;
}
