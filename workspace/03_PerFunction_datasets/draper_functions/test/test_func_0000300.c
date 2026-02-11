pp_c_floating_constant (c_pretty_printer *pp, tree r)
{
  real_to_decimal (pp_buffer (pp)->digit_buffer, &TREE_REAL_CST (r),
		   sizeof (pp_buffer (pp)->digit_buffer), 0, 1);
  pp_string (pp, pp_buffer(pp)->digit_buffer);
  if (TREE_TYPE (r) == float_type_node)
    pp_character (pp, 'f');
  else if (TREE_TYPE (r) == long_double_type_node)
    pp_character (pp, 'l');
}
