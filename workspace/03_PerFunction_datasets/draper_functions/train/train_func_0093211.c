test_get_events_text (WalkerTestCaseFixture *fixture,
    TplLogWalker *walker,
    guint num_events,
    gint64 timestamp,
    const gchar *message)
{
  GList *events;

  get_events (fixture, walker, num_events);

  events = fixture->events;
  g_assert (events != NULL);
  g_assert_cmpuint (g_list_length (events), ==, num_events);
  g_assert_cmpint (tpl_event_get_timestamp (TPL_EVENT (events->data)),
      ==,
      timestamp);
  g_assert_cmpstr (tpl_text_event_get_message (TPL_TEXT_EVENT (events->data)),
      ==,
      message);
  g_list_free_full (events, g_object_unref);
}
