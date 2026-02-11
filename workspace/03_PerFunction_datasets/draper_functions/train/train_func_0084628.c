oom (const gchar *explanation)
{
  g_error ("%s", explanation == NULL ? "Out of memory" : explanation);
  g_assert_not_reached ();
}
