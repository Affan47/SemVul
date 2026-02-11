toCtype (void)
{
  if (!ctype)
    {
      if (!sym->memtype->isintegral() || sym->memtype->ty == Tbool)
	{


	  ctype = sym->memtype->toCtype();
	}
      else
	{
	  tree cmemtype = sym->memtype->toCtype();

	  ctype = make_node (ENUMERAL_TYPE);
	  TYPE_LANG_SPECIFIC (ctype) = build_d_type_lang_specific (this);
	  d_keep (ctype);

	  if (flag_short_enums)
	    TYPE_PACKED (ctype) = 1;

	  TYPE_PRECISION (ctype) = size (sym->loc) * 8;
	  TYPE_SIZE (ctype) = 0;

	  if (sym->userAttributes)
	    decl_attributes (&ctype, build_attributes (sym->userAttributes),
			     ATTR_FLAG_TYPE_IN_PLACE);

	  TYPE_MIN_VALUE (ctype) = TYPE_MIN_VALUE (cmemtype);
	  TYPE_MAX_VALUE (ctype) = TYPE_MAX_VALUE (cmemtype);
	  layout_type (ctype);
	  TYPE_UNSIGNED (ctype) = TYPE_UNSIGNED (cmemtype);

	  tree enum_values = NULL_TREE;
	  if (sym->members)
	    {
	      for (size_t i = 0; i < sym->members->dim; i++)
		{
		  EnumMember *member = (*sym->members)[i]->isEnumMember();

		  if (member == NULL)
		    continue;

		  tree ident = get_identifier (member->ident->string);
		  tree value = build_integer_cst (member->value->toInteger(), cmemtype);


		  tree decl = build_decl (UNKNOWN_LOCATION, CONST_DECL, ident, cmemtype);
		  set_decl_location (decl, member->loc);
		  DECL_CONTEXT (decl) = ctype;
		  TREE_CONSTANT (decl) = 1;
		  TREE_READONLY (decl) = 1;
		  DECL_INITIAL (decl) = value;


		  enum_values = chainon (enum_values, build_tree_list (ident, decl));
		}
	    }

	  TYPE_VALUES (ctype) = enum_values;
	  build_type_decl (ctype, sym);
	}
    }

  return ctype;
}
