clock_timer_callback (gpointer data)
{
  Clock *clock = (Clock *) data;

  GDK_THREADS_ENTER ();
  clock_gen_str (clock);
  GDK_THREADS_LEAVE ();

  return TRUE;
}
