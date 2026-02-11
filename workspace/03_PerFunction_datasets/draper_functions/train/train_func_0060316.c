clutter_threads_set_lock_functions (GCallback enter_fn,
                                    GCallback leave_fn)
{
  g_return_if_fail (clutter_threads_lock == NULL &&
                    clutter_threads_unlock == NULL);

  clutter_threads_lock = enter_fn;
  clutter_threads_unlock = leave_fn;
}
