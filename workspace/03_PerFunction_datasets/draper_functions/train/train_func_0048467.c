s48_extract_pointer_2(s48_call_t call, s48_ref_t sch_pointer)
{
  s48_check_value_2(call, sch_pointer);
  return *(s48_address_after_header_2(call, sch_pointer, void *));
}
