dump_type_prefix (tree t, int flags)
{
  if (TYPE_PTRMEMFUNC_P (t))
    {
      t = TYPE_PTRMEMFUNC_FN_TYPE (t);
      goto offset_type;
    }

  switch (TREE_CODE (t))
    {
    case POINTER_TYPE:
    case REFERENCE_TYPE:
      {
	tree sub = TREE_TYPE (t);

	dump_type_prefix (sub, flags);
	if (TREE_CODE (sub) == ARRAY_TYPE
	    || TREE_CODE (sub) == FUNCTION_TYPE)
	  {
	    pp_cxx_whitespace (cxx_pp);
	    pp_cxx_left_paren (cxx_pp);
	    pp_c_attributes_display (pp_c_base (cxx_pp),
				     TYPE_ATTRIBUTES (sub));
	  }
	if (TREE_CODE (t) == POINTER_TYPE)
	  pp_character(cxx_pp, '*');
	else if (TREE_CODE (t) == REFERENCE_TYPE)
	{
	  if (TYPE_REF_IS_RVALUE (t))
	    pp_string (cxx_pp, "&&");
	  else
	    pp_character (cxx_pp, '&');
	}
	pp_base (cxx_pp)->padding = pp_before;
	pp_cxx_cv_qualifier_seq (cxx_pp, t);
      }
      break;

    case OFFSET_TYPE:
    offset_type:
      dump_type_prefix (TREE_TYPE (t), flags);
      if (TREE_CODE (t) == OFFSET_TYPE)
	{
	  pp_maybe_space (cxx_pp);
	  if (TREE_CODE (TREE_TYPE (t)) == ARRAY_TYPE)
	     pp_cxx_left_paren (cxx_pp);
	  dump_type (TYPE_OFFSET_BASETYPE (t), flags);
	  pp_cxx_colon_colon (cxx_pp);
	}
      pp_cxx_star (cxx_pp);
      pp_cxx_cv_qualifier_seq (cxx_pp, t);
      pp_base (cxx_pp)->padding = pp_before;
      break;


    case FUNCTION_TYPE:
      dump_type_prefix (TREE_TYPE (t), flags);
      break;

    case METHOD_TYPE:
      dump_type_prefix (TREE_TYPE (t), flags);
      pp_maybe_space (cxx_pp);
      pp_cxx_left_paren (cxx_pp);
      dump_aggr_type (TYPE_METHOD_BASETYPE (t), flags);
      pp_cxx_colon_colon (cxx_pp);
      break;

    case ARRAY_TYPE:
      dump_type_prefix (TREE_TYPE (t), flags);
      break;

    case ENUMERAL_TYPE:
    case IDENTIFIER_NODE:
    case INTEGER_TYPE:
    case BOOLEAN_TYPE:
    case REAL_TYPE:
    case RECORD_TYPE:
    case TEMPLATE_TYPE_PARM:
    case TEMPLATE_TEMPLATE_PARM:
    case BOUND_TEMPLATE_TEMPLATE_PARM:
    case TREE_LIST:
    case TYPE_DECL:
    case TREE_VEC:
    case UNION_TYPE:
    case LANG_TYPE:
    case VOID_TYPE:
    case TYPENAME_TYPE:
    case COMPLEX_TYPE:
    case VECTOR_TYPE:
    case TYPEOF_TYPE:
    case UNDERLYING_TYPE:
    case DECLTYPE_TYPE:
    case TYPE_PACK_EXPANSION:
    case FIXED_POINT_TYPE:
    case NULLPTR_TYPE:
      dump_type (t, flags);
      pp_base (cxx_pp)->padding = pp_before;
      break;

    default:
      pp_unsupported_tree (cxx_pp, t);

    case ERROR_MARK:
      pp_string (cxx_pp, M_("<typeprefixerror>"));
      break;
    }
}
