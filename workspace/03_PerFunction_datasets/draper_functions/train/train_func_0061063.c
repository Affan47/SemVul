ffi_record_ref(s48_call_t call,
	       s48_ref_t sch_record,
	       s48_ref_t sch_index)
{
  int index = s48_extract_long_2(call, sch_index);
  long rec_len = s48_record_length_2(call, sch_record);
  s48_ref_t result = s48_unspecific_2(call);
  if (index < rec_len)
    {
      result = s48_record_ref_2(call, sch_record, index);
    }
  return result;
}
