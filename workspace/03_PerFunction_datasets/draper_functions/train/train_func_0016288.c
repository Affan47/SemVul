assemble_external_libcall (fun)
     rtx fun ATTRIBUTE_UNUSED;
{
#ifdef ASM_OUTPUT_EXTERNAL_LIBCALL

  if (! SYMBOL_REF_USED (fun))
    {
      SYMBOL_REF_USED (fun) = 1;
      ASM_OUTPUT_EXTERNAL_LIBCALL (asm_out_file, fun);
    }
#endif
}
