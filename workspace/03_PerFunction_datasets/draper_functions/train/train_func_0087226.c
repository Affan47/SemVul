main (gint argc, gchar * argv[])
{
  GThread *threads[MAX_THREADS];
  gint num_threads;
  gint t;

  gst_init (&argc, &argv);

  fdlock = g_mutex_new ();
  timer = g_timer_new ();

  if (argc != 2) {
    g_print ("usage: %s <num_threads>\n", argv[0]);
    exit (-1);
  }

  num_threads = atoi (argv[1]);

  set = gst_poll_new (TRUE);

  for (t = 0; t < num_threads; t++) {
    GError *error = NULL;

#if !GLIB_CHECK_VERSION (2, 31, 0)
    threads[t] = g_thread_create (run_test, GINT_TO_POINTER (t), TRUE, &error);
#else
    threads[t] = g_thread_try_new ("pollstresstest", run_test,
        GINT_TO_POINTER (t), &error);
#endif
    if (error) {
      printf ("ERROR: g_thread_create() %s\n", error->message);
      exit (-1);
    }
  }
  printf ("main(): Created %d threads.\n", t);

  for (t = 0; t < num_threads; t++) {
    g_thread_join (threads[t]);
  }

  gst_poll_free (set);

  return 0;
}
