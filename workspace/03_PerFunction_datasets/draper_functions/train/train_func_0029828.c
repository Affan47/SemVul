dwarf2dbg_convert_frag (fragS *frag)
{
  offsetT addr_diff;

  if (DWARF2_USE_FIXED_ADVANCE_PC)
    {


      int saved_finalize_syms = finalize_syms;

      finalize_syms = 0;
      addr_diff = resolve_symbol_value (frag->fr_symbol);
      finalize_syms = saved_finalize_syms;
    }
  else
    addr_diff = resolve_symbol_value (frag->fr_symbol);


  gas_assert (frag->fr_var >= (int) frag->fr_subtype);

  if (DWARF2_USE_FIXED_ADVANCE_PC)
    emit_fixed_inc_line_addr (frag->fr_offset, addr_diff, frag,
			      frag->fr_literal + frag->fr_fix,
			      frag->fr_subtype);
  else
    emit_inc_line_addr (frag->fr_offset, addr_diff,
			frag->fr_literal + frag->fr_fix, frag->fr_subtype);

  frag->fr_fix += frag->fr_subtype;
  frag->fr_type = rs_fill;
  frag->fr_var = 0;
  frag->fr_offset = 0;
}
