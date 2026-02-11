fast_math_flags_set_p (const struct gcc_options *opts)
{
  return (!opts->x_flag_trapping_math
	  && opts->x_flag_unsafe_math_optimizations
	  && opts->x_flag_finite_math_only
	  && !opts->x_flag_signed_zeros
	  && !opts->x_flag_errno_math);
}
