lookup_name (tree name)
{
  struct c_binding *b = I_SYMBOL_BINDING (name);
  if (b && !b->invisible)
    return b->decl;
  return 0;
}
