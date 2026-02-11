offset_address (rtx memref, rtx offset, unsigned HOST_WIDE_INT pow2)
{
  rtx new_rtx, addr = XEXP (memref, 0);
  enum machine_mode address_mode;
  struct mem_attrs attrs, *defattrs;

  attrs = *get_mem_attrs (memref);
  address_mode = get_address_mode (memref);
  new_rtx = simplify_gen_binary (PLUS, address_mode, addr, offset);


  if (! memory_address_addr_space_p (GET_MODE (memref), new_rtx,
				     attrs.addrspace)
      && GET_CODE (addr) == PLUS
      && XEXP (addr, 0) == pic_offset_table_rtx)
    {
      addr = force_reg (GET_MODE (addr), addr);
      new_rtx = simplify_gen_binary (PLUS, address_mode, addr, offset);
    }

  update_temp_slot_address (XEXP (memref, 0), new_rtx);
  new_rtx = change_address_1 (memref, VOIDmode, new_rtx, 1);


  if (new_rtx == memref)
    return new_rtx;


  defattrs = mode_mem_attrs[(int) GET_MODE (new_rtx)];
  attrs.offset_known_p = false;
  attrs.size_known_p = defattrs->size_known_p;
  attrs.size = defattrs->size;
  attrs.align = MIN (attrs.align, pow2 * BITS_PER_UNIT);
  set_mem_attrs (new_rtx, &attrs);
  return new_rtx;
}
