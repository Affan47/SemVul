_eef_inst_func_incdec_regpair (eef_addr_t opnd_addr, gchar r, gboolean is_inc)
{
  gint bytes_consumed = 0;
  gint dx = -1;
  eef_data_t *rloc_h, *rloc_l;

  if (is_inc)
	dx = +1;
  eef_loc_of_regpair (r, &rloc_h, &rloc_l);
  *rloc_l += dx;
  if (*rloc_l == 0xFF && dx == -1)
	*rloc_h += dx;
  else if (*rloc_l == 0x00 && dx == +1)
	*rloc_h += dx;


  return bytes_consumed;
}
