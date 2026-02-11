pp_c_declaration_specifiers (c_pretty_printer *pp, tree t)
{
  pp_storage_class_specifier (pp, t);
  pp_function_specifier (pp, t);
  pp_c_specifier_qualifier_list (pp, DECL_P (t) ?  TREE_TYPE (t) : t);
}
