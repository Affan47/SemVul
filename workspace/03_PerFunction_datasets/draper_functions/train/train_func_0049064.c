output_constant_def_contents (rtx symbol)
{
  tree exp = SYMBOL_REF_DECL (symbol);
  const char *label = XSTR (symbol, 0);
  HOST_WIDE_INT size;


  int reloc = compute_reloc_for_constant (exp);


  int align = TYPE_ALIGN (TREE_TYPE (exp));
#ifdef CONSTANT_ALIGNMENT
  align = CONSTANT_ALIGNMENT (exp, align);
#endif

  output_addressed_constants (exp);


  TREE_ASM_WRITTEN (exp) = 1;

  if (IN_NAMED_SECTION (exp))
    named_section (exp, NULL, reloc);
  else
    (*targetm.asm_out.select_section) (exp, reloc, align);

  if (align > BITS_PER_UNIT)
    {
      ASM_OUTPUT_ALIGN (asm_out_file, floor_log2 (align / BITS_PER_UNIT));
    }

  size = int_size_in_bytes (TREE_TYPE (exp));
  if (TREE_CODE (exp) == STRING_CST)
    size = MAX (TREE_STRING_LENGTH (exp), size);


#ifdef ASM_DECLARE_CONSTANT_NAME
  ASM_DECLARE_CONSTANT_NAME (asm_out_file, label, exp, size);
#else

  ASM_OUTPUT_LABEL (asm_out_file, label);
#endif


  output_constant (exp, size, align);
}
