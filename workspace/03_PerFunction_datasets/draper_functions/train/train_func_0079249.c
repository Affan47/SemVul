accumulate_cancel_on_first (gpointer result,
                            gpointer user_data)
{
  GCancellable *cancellable = G_CANCELLABLE (user_data);
  g_assert (!g_cancellable_is_cancelled (cancellable));
  g_cancellable_cancel (cancellable);
  return TRUE;
}
