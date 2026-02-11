watchdog_timeout (gpointer data)
{
  TestState *state = data;

  g_test_message ("Watchdog timer kicking in");
  g_test_message ("rewind_count=%i", state->rewind_count);
  if (state->rewind_count <= 3)
    {

      g_test_message ("Failed (This test shouldn't have hung!)");
      exit (EXIT_FAILURE);
    }
  else
    {
      g_test_message ("Passed");
      clutter_main_quit ();
    }

  return G_SOURCE_REMOVE;
}
