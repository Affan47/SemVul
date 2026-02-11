objc_printable_name (tree decl, int v)
{
  const char *demangled_name = objc_maybe_printable_name (decl, v);

  if (demangled_name != NULL)
    return demangled_name;
  else
    return IDENTIFIER_POINTER (DECL_NAME (decl));
}
