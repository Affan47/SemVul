gate_asan (void)
{
  return flag_asan != 0
	  && !lookup_attribute ("no_sanitize_address",
				DECL_ATTRIBUTES (current_function_decl));
}
