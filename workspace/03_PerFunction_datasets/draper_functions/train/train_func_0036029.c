dwarf2out_emit_cfi (dw_cfi_ref cfi)
{
  if (dwarf2out_do_cfi_asm ())
    output_cfi_directive (asm_out_file, cfi);
}
