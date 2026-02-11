get_spill_slot_decl (bool force_build_p)
{
  tree d = spill_slot_decl;
  rtx rd;

  if (d || !force_build_p)
    return d;

  d = build_decl (DECL_SOURCE_LOCATION (current_function_decl),
		  VAR_DECL, get_identifier ("%sfp"), void_type_node);
  DECL_ARTIFICIAL (d) = 1;
  DECL_IGNORED_P (d) = 1;
  TREE_USED (d) = 1;
  spill_slot_decl = d;

  rd = gen_rtx_MEM (BLKmode, frame_pointer_rtx);
  MEM_NOTRAP_P (rd) = 1;
  MEM_ATTRS (rd) = get_mem_attrs (new_alias_set (), d, const0_rtx,
				  NULL_RTX, 0, ADDR_SPACE_GENERIC, BLKmode);
  SET_DECL_RTL (d, rd);

  return d;
}
