bfd_symbol_info (asymbol *symbol, symbol_info *ret)
{
  ret->type = bfd_decode_symclass (symbol);

  if (bfd_is_undefined_symclass (ret->type))
    ret->value = 0;
  else
    ret->value = symbol->value + symbol->section->vma;

  ret->name = symbol->name;
}
