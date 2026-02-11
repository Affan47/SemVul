ok(int pass, char const *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);

  if (!pass && *g_test.todo == '\0')
    ++g_test.failed;

  vemit_tap(pass, fmt, ap);
  va_end(ap);
  if (*g_test.todo != '\0')
    emit_dir("todo", g_test.todo);
  emit_endl();
}
