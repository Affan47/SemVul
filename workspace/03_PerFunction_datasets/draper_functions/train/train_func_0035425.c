main_context_acquire_wait (GMainContext *context)
{
  while (!g_main_context_wait (context, cond, mutex));
}
