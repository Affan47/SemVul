m_vaul_print_to_ostream (pIIR_AttrTypeFunc n, ostream &o)
{
  o << n->prefix << "'" << attr_name (n);
  if (n->argument)
    o << "(...)";
}
