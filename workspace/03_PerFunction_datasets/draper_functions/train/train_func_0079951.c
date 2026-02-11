dwarf2out_do_cfi_asm (void)
{
  int enc;

#ifdef MIPS_DEBUGGING_INFO
  return false;
#endif

  if (saved_do_cfi_asm != 0)
    return saved_do_cfi_asm > 0;


  saved_do_cfi_asm = -1;

  if (!flag_dwarf2_cfi_asm || !dwarf2out_do_frame ())
    return false;
  if (!HAVE_GAS_CFI_PERSONALITY_DIRECTIVE)
    return false;


  enc = ASM_PREFERRED_EH_DATA_FORMAT (2,1);
  if ((enc & 0x70) != 0 && (enc & 0x70) != DW_EH_PE_pcrel)
    return false;
  enc = ASM_PREFERRED_EH_DATA_FORMAT (0,0);
  if ((enc & 0x70) != 0 && (enc & 0x70) != DW_EH_PE_pcrel)
    return false;


  if (!HAVE_GAS_CFI_SECTIONS_DIRECTIVE
      && !flag_unwind_tables && !flag_exceptions
      && targetm_common.except_unwind_info (&global_options) != UI_DWARF2)
    return false;


  saved_do_cfi_asm = 1;
  return true;
}
