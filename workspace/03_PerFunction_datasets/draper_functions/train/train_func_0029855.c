pp_cxx_pm_expression (cxx_pretty_printer *pp, tree t)
{
  switch (TREE_CODE (t))
    {

    case OFFSET_REF:
      if (TYPE_P (TREE_OPERAND (t, 0)))
        {
          pp_cxx_qualified_id (pp, t);
          break;
        }

    case MEMBER_REF:
    case DOTSTAR_EXPR:
      pp_cxx_pm_expression (pp, TREE_OPERAND (t, 0));
      pp_cxx_dot (pp);
      pp_star(pp);
      pp_cxx_cast_expression (pp, TREE_OPERAND (t, 1));
      break;


    default:
      pp_cxx_cast_expression (pp, t);
      break;
    }
}
