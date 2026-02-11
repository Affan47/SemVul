escp2_set_resolution(stp_vars_t *v)
{
  escp2_privdata_t *pd = get_privdata(v);
  if (pd->use_extended_commands)
    stp_send_command(v, "\033(U", "bccch",
		     pd->unit_scale / pd->page_management_units,
		     pd->unit_scale / pd->vertical_units,
		     pd->unit_scale / pd->horizontal_units,
		     pd->unit_scale);
  else
    stp_send_command(v, "\033(U", "bc",
		     pd->unit_scale / pd->page_management_units);
}
