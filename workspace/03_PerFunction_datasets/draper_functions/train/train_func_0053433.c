offset_address (memref, offset, pow2)
     rtx memref;
     rtx offset;
     HOST_WIDE_INT pow2;
{
  rtx new, addr = XEXP (memref, 0);

  new = simplify_gen_binary (PLUS, Pmode, addr, offset);


  if (! memory_address_p (GET_MODE (memref), new)
      && GET_CODE (addr) == PLUS
      && XEXP (addr, 0) == pic_offset_table_rtx)
    {
      addr = force_reg (GET_MODE (addr), addr);
      new = simplify_gen_binary (PLUS, Pmode, addr, offset);
    }

  update_temp_slot_address (XEXP (memref, 0), new);
  new = change_address_1 (memref, VOIDmode, new, 1);


  MEM_ATTRS (new)
    = get_mem_attrs (MEM_ALIAS_SET (memref), MEM_EXPR (memref), 0, 0,
		     MIN (MEM_ALIGN (memref),
			  (unsigned HOST_WIDE_INT) pow2 * BITS_PER_UNIT),
		     GET_MODE (new));
  return new;
}
