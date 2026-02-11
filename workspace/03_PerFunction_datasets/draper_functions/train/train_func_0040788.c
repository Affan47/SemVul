init_mangle (void)
{
  gcc_obstack_init (&name_obstack);
  name_base = obstack_alloc (&name_obstack, 0);
  G.substitutions = NULL;


  subst_identifiers[SUBID_ALLOCATOR] = get_identifier ("allocator");
  subst_identifiers[SUBID_BASIC_STRING] = get_identifier ("basic_string");
  subst_identifiers[SUBID_CHAR_TRAITS] = get_identifier ("char_traits");
  subst_identifiers[SUBID_BASIC_ISTREAM] = get_identifier ("basic_istream");
  subst_identifiers[SUBID_BASIC_OSTREAM] = get_identifier ("basic_ostream");
  subst_identifiers[SUBID_BASIC_IOSTREAM] = get_identifier ("basic_iostream");
}
