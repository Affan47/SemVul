s48_stob_set_2(s48_call_t call, s48_ref_t thing, int type, long offset, s48_ref_t value)
{
  long length;

  if (!(s48_stob_p_2(call, thing) &&
	(s48_stob_type_2(call, thing) == type) &&
	!s48_stob_immutablep_2(call, thing)))
    s48_assertion_violation_2(call, "s48_stob_set_2",
			      "not a mutable stob", 1, thing);

  length = s48_unsafe_stob_descriptor_length_2(call, thing);

  if (offset < 0 || length <= offset)
    s48_assertion_violation_2(call, "s48_stob_set_2", "invalid stob index", 3,
			      s48_enter_integer(offset),
			      s48_unsafe_enter_long_as_fixnum_2(call, 0),
			      s48_unsafe_enter_long_as_fixnum_2(call, length - 1));

  s48_unsafe_stob_set_2(call, thing, offset, value);
}
