check_scalar_against_bounds(pIIR_Root n, StaticDataType &value, pIIR_Type target_type, RegionStack &rstack,
			    RuntimeCheckFlags &runtime_checks, bool print_error,
			    string error_prefix_str)
{
  if (get_base_type(target_type)->is(IR_FLOATING_TYPE))
    return check_scalar_against_bounds(n, value.double_value(), target_type, rstack, runtime_checks,
				       print_error, error_prefix_str);
  else
    return check_scalar_against_bounds(n, value.long_value(), target_type, rstack, runtime_checks,
				       print_error, error_prefix_str);
}
