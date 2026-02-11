push_conditional (GISourceScanner *scanner,
                  gint type)
{
  g_assert (type != 0);
  g_queue_push_head (&scanner->conditionals, GINT_TO_POINTER (type));
}
