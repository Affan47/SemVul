set_mem_attrs_for_spill (rtx mem)
{
  struct mem_attrs attrs;
  rtx addr;

  attrs = *get_mem_attrs (mem);
  attrs.expr = get_spill_slot_decl (true);
  attrs.alias = MEM_ALIAS_SET (DECL_RTL (attrs.expr));
  attrs.addrspace = ADDR_SPACE_GENERIC;


  addr = XEXP (mem, 0);
  attrs.offset_known_p = true;
  attrs.offset = 0;
  if (GET_CODE (addr) == PLUS
      && CONST_INT_P (XEXP (addr, 1)))
    attrs.offset = INTVAL (XEXP (addr, 1));

  set_mem_attrs (mem, &attrs);
  MEM_NOTRAP_P (mem) = 1;
}
