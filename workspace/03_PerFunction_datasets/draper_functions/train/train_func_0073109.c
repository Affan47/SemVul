my_xerror (int severity,
           po_message_t message,
           const char *filename, size_t lineno, size_t column,
           int multiline_p, const char *message_text)
{
  printf ("xerror called:\n  %s\n", message_text);
  if (severity == PO_SEVERITY_FATAL_ERROR)
    abort ();
  num_errors++;
}
