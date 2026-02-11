report_error(uint code, const char *fmt, ...)
{
  va_list args;
  char buf[512];

  va_start(args, fmt);
  my_vsnprintf(buf, sizeof(buf), fmt, args);
  va_end(args);

  if (code)
    my_message(code, buf, MYF(0));
  else
    my_error(ER_CANNOT_LOAD_FROM_TABLE, MYF(0), "proc");

  if (m_print_once)
  {
    m_print_once= FALSE;
    sql_print_error("%s", buf);
  }
}
