on_threaded_job_completed (UDisksThreadedJob  *job,
                           gboolean            result,
                           GError             *error,
                           gpointer            user_data)
{
  gboolean *handler_ran = user_data;
  g_assert (g_thread_self () == main_thread);
  g_assert (!result);
  g_assert_error (error, G_KEY_FILE_ERROR, G_KEY_FILE_ERROR_INVALID_VALUE);
  g_assert (!*handler_ran);
  *handler_ran = TRUE;
  return FALSE;
}
