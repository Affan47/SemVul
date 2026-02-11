initiate_states (void)
{
  decl_t decl;
  int i;

  if (description->units_num)
    units_array = XNEWVEC (unit_decl_t, description->units_num);
  else
    units_array = 0;

  for (i = 0; i < description->decls_num; i++)
    {
      decl = description->decls [i];
      if (decl->mode == dm_unit)
	units_array [DECL_UNIT (decl)->unit_num] = DECL_UNIT (decl);
    }
  max_cycles_num = description->max_insn_reserv_cycles;
  els_in_cycle_reserv
    = ((description->units_num + sizeof (set_el_t) * CHAR_BIT - 1)
       / (sizeof (set_el_t) * CHAR_BIT));
  els_in_reservs = els_in_cycle_reserv * max_cycles_num;
  curr_unique_state_num = 0;
  initiate_alt_states ();
  state_table = htab_create (1500, state_hash, state_eq_p, (htab_del) 0);
  temp_reserv = alloc_empty_reserv_sets ();
}
