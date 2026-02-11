raise_wakeup (GstPoll * set)
{
  gboolean result = TRUE;

  if (G_ATOMIC_INT_ADD (&set->control_pending, 1) == 0) {

    result = WAKE_EVENT (set);
  }
  return result;
}
