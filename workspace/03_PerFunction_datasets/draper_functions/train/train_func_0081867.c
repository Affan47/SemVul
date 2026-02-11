s48_enter_char_2(s48_call_t call, long a_char)
{
  if (! ((a_char >= 0)
	 && ((a_char <= 0xd7ff)
	     || ((a_char >= 0xe000) && (a_char <= 0x10ffff)))))
    s48_assertion_violation_2(call, "s48_enter_char_2",
			      "not a scalar value", 1, s48_enter_long_as_fixnum_2(call, a_char));

  return s48_unsafe_enter_char_2(call, a_char);
}
