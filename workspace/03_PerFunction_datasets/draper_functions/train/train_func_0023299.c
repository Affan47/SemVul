atoi_p (char *string_num, int *integer_p_ptr)
{
  int num = 0, i, string_length, a_char;

  string_length = strlen(string_num);
  *integer_p_ptr = TRUE;
  for (i=0; i<string_length; i++) {
    a_char = (int) string_num[i];
    if ((a_char >= '0') && (a_char <= '9'))
      continue;
    if ((a_char == '+') || (a_char == '-'))
      continue;
    *integer_p_ptr = FALSE;
    break;
  }
  if (string_length == 0)
    *integer_p_ptr = FALSE;

  if (*integer_p_ptr == TRUE)
    num = atoi(string_num);
  return(num);
}
