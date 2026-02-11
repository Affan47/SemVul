pp_cxx_canonical_template_parameter (cxx_pretty_printer *pp, tree parm)
{
  const enum tree_code code = TREE_CODE (parm);


  if (code == TEMPLATE_TYPE_PARM || code == TEMPLATE_TEMPLATE_PARM
      || code == BOUND_TEMPLATE_TEMPLATE_PARM)
    parm = TEMPLATE_TYPE_PARM_INDEX (parm);

  pp_cxx_begin_template_argument_list (pp);
  pp_cxx_ws_string (pp, M_("template-parameter-"));
  pp_wide_integer (pp, TEMPLATE_PARM_LEVEL (parm));
  pp_minus (pp);
  pp_wide_integer (pp, TEMPLATE_PARM_IDX (parm) + 1);
  pp_cxx_end_template_argument_list (pp);
}
