range_to_dstring(u_long32 start, u_long32 end, int step,
                      dstring * dyn_taskrange_str, int ignore_step,
                      bool use_comma_as_separator, bool print_always_as_range)
{
   char tail[256] = "";
   char to_char = '-';
   char step_char = ':';

   if (use_comma_as_separator) {
      to_char = ',';
      step_char = ',';
   }
   if (dyn_taskrange_str->length > 0) {
      sge_dstring_append(dyn_taskrange_str, ",");
   }

   if (start == end && !print_always_as_range) {
      sprintf(tail, sge_u32, start);
   } else if (start == end && print_always_as_range) {
      sprintf(tail, sge_u32 "%c" sge_u32, start, to_char, end);
   } else if (start + step == end) {
      sprintf(tail, sge_u32 "," sge_u32, start, end);
   } else {
      if (ignore_step) {
         sprintf(tail, sge_u32 "%c" sge_u32, start, to_char, end);
      } else {
         sprintf(tail, sge_u32 "%c" sge_u32 "%c%d", start, to_char, end, step_char, step);
      }
   }
   sge_dstring_append(dyn_taskrange_str, tail);
}
