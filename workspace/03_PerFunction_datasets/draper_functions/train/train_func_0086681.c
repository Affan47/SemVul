temp_slots_at_level (int level)
{
  if (level >= (int) VEC_length (temp_slot_p, used_temp_slots))
    VEC_safe_grow_cleared (temp_slot_p, gc, used_temp_slots, level + 1);

  return &(VEC_address (temp_slot_p, used_temp_slots)[level]);
}
