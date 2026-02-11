xlate_g_print (const char *text)
{
  console_lock ();
  xlate_write (text, STDOUT);
  console_push (text, 0);
  set_prev_line (text);
  console_unlock ();
}
