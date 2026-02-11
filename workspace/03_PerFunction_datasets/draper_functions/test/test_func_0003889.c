maybe_print_constexpr_context (diagnostic_context *context)
{
  VEC(tree,heap) *call_stack = cx_error_context ();
  unsigned ix;
  tree t;

  FOR_EACH_VEC_ELT (tree, call_stack, ix, t)
    {
      expanded_location xloc = expand_location (EXPR_LOCATION (t));
      const char *s = expr_as_string (t, 0);
      if (context->show_column)
	pp_verbatim (context->printer,
		     _("%s:%d:%d:   in constexpr expansion of %qs"),
		     xloc.file, xloc.line, xloc.column, s);
      else
	pp_verbatim (context->printer,
		     _("%s:%d:   in constexpr expansion of %qs"),
		     xloc.file, xloc.line, s);
      pp_base_newline (context->printer);
    }
}
