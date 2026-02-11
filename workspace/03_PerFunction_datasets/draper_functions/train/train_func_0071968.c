changed (DConfClient         *client,
         const gchar         *prefix,
         const gchar * const *changes,
         const gchar         *tag,
         gpointer             user_data)
{
  g_assert (g_thread_self () == main_thread);

  changed_was_called = TRUE;
}
