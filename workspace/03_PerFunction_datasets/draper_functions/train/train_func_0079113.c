do_tests (CallbackData *data)
{
  while (data)
    {
        gboolean result = check_result (data);
        g_assert (result == FALSE);
        data = data->next;
    }

  clutter_main_quit ();

  return FALSE;
}
