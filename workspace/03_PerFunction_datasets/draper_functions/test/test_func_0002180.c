finish_states (void)
{
  VLA_PTR_DELETE (units_container);
  htab_delete (state_table);
  VLA_PTR_DELETE (free_states);
  finish_alt_states ();
}
