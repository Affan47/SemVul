posix_get_terminal_pathname(s48_call_t call)
{
  char termid[L_ctermid];
  char *status =  ctermid(termid);

  return (*status == '\0') ? s48_false_2(call) : s48_enter_byte_string_2(call, termid);
}
