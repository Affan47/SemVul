delete_variable_part (dataflow_set *set, rtx loc, decl_or_value dv,
		      HOST_WIDE_INT offset)
{
  void **slot = shared_hash_find_slot_noinsert (set->vars, dv);
  if (!slot)
    return;

  delete_slot_part (set, loc, slot, offset);
}
