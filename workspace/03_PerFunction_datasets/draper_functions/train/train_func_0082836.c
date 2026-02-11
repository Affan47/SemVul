add_abstract_origin_attribute (die, origin)
     dw_die_ref die;
     tree origin;
{
  dw_die_ref origin_die = NULL;

  if (TREE_CODE (origin) != FUNCTION_DECL)
    {


      tree fn = origin;

      if (TYPE_P (fn))
	fn = TYPE_STUB_DECL (fn);

      fn = decl_function_context (fn);
      if (fn)
	dwarf2out_abstract_function (fn);
    }

  if (DECL_P (origin))
    origin_die = lookup_decl_die (origin);
  else if (TYPE_P (origin))
    origin_die = lookup_type_die (origin);

  if (origin_die == NULL)
    abort ();

  add_AT_die_ref (die, DW_AT_abstract_origin, origin_die);
}
