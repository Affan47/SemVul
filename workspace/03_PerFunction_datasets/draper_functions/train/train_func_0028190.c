init_temp_slots (void)
{

  avail_temp_slots = 0;
  vec_alloc (used_temp_slots, 0);
  temp_slot_level = 0;
  n_temp_slots_in_use = 0;


  if (! temp_slot_address_table)
    temp_slot_address_table = htab_create_ggc (32,
					       temp_slot_address_hash,
					       temp_slot_address_eq,
					       NULL);
  else
    htab_empty (temp_slot_address_table);
}
