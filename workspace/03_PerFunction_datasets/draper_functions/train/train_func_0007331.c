pp_cxx_qualified_id (cxx_pretty_printer *pp, tree t)
{
  switch (TREE_CODE (t))
    {

    case PTRMEM_CST:
      pp_cxx_nested_name_specifier (pp, PTRMEM_CST_CLASS (t));
      pp_cxx_unqualified_id (pp, PTRMEM_CST_MEMBER (t));
      break;


    case OVERLOAD:
      t = OVL_CURRENT (t);
    case FUNCTION_DECL:
      if (DECL_FUNCTION_MEMBER_P (t))
	pp_cxx_nested_name_specifier (pp, DECL_CONTEXT (t));
      pp_cxx_unqualified_id
	(pp, DECL_CONSTRUCTOR_P (t) ? DECL_CONTEXT (t) : t);
      pp_cxx_parameter_declaration_clause (pp, TREE_TYPE (t));
      break;

    case OFFSET_REF:
    case SCOPE_REF:
      pp_cxx_nested_name_specifier (pp, TREE_OPERAND (t, 0));
      pp_cxx_unqualified_id (pp, TREE_OPERAND (t, 1));
      break;

    default:
      {
	tree scope = TYPE_P (t) ? TYPE_CONTEXT (t) : DECL_CONTEXT (t);
	if (scope != pp->enclosing_scope)
	  {
	    pp_cxx_nested_name_specifier (pp, scope);
	    pp_cxx_template_keyword_if_needed (pp, scope, t);
	  }
	pp_cxx_unqualified_id (pp, t);
      }
      break;
    }
}
