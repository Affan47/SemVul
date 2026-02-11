vn_reference_lookup_2 (ao_ref *op ATTRIBUTE_UNUSED, tree vuse,
		       unsigned int cnt, void *vr_)
{
  vn_reference_t vr = (vn_reference_t)vr_;
  void **slot;
  hashval_t hash;


  if (cnt > (unsigned) PARAM_VALUE (PARAM_SCCVN_MAX_ALIAS_QUERIES_PER_ACCESS))
    return (void *)-1;

  if (last_vuse_ptr)
    *last_vuse_ptr = vuse;


  if (vr->vuse)
    vr->hashcode = vr->hashcode - SSA_NAME_VERSION (vr->vuse);
  vr->vuse = SSA_VAL (vuse);
  if (vr->vuse)
    vr->hashcode = vr->hashcode + SSA_NAME_VERSION (vr->vuse);

  hash = vr->hashcode;
  slot = htab_find_slot_with_hash (current_info->references, vr,
				   hash, NO_INSERT);
  if (!slot && current_info == optimistic_info)
    slot = htab_find_slot_with_hash (valid_info->references, vr,
				     hash, NO_INSERT);
  if (slot)
    return *slot;

  return NULL;
}
