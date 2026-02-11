validate_substring_args (SCM str, size_t start, size_t end)
{
  if (!IS_STRING (str))
    scm_wrong_type_arg_msg (NULL, 0, str, "string");
  if (start > STRING_LENGTH (str))
    scm_out_of_range (NULL, scm_from_size_t (start));
  if (end > STRING_LENGTH (str) || end < start)
    scm_out_of_range (NULL, scm_from_size_t (end));
}
