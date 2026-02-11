objdump_symbol_at_address (bfd_vma vma, struct disassemble_info * inf)
{
  asymbol * sym;

  sym = find_symbol_for_address (vma, inf, NULL);

  return (sym != NULL && (bfd_asymbol_value (sym) == vma));
}
