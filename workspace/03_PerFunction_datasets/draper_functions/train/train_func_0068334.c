record_vop_access (htab_t vop_to_refs, unsigned vop, unsigned ref, bool stored)
{
  void **slot = htab_find_slot_with_hash (vop_to_refs, &vop, vop, INSERT);
  struct vop_to_refs_elt *vtoe;

  if (!*slot)
    {
      vtoe = XNEW (struct vop_to_refs_elt);
      vtoe->uid = vop;
      vtoe->refs_all = BITMAP_ALLOC (NULL);
      vtoe->refs_stored = BITMAP_ALLOC (NULL);
      *slot = vtoe;
    }
  else
    vtoe = (struct vop_to_refs_elt *) *slot;

  bitmap_set_bit (vtoe->refs_all, ref);
  if (stored)
    bitmap_set_bit (vtoe->refs_stored, ref);
}
