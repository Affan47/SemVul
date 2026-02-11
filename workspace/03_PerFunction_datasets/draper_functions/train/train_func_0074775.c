scm_i_with_guile_and_parent (void *(*func)(void *), void *data,
			     SCM parent)
{
  void *res;
  int really_entered;
  SCM_STACKITEM base_item;
  really_entered = scm_i_init_thread_for_guile (&base_item, parent);
  res = scm_c_with_continuation_barrier (func, data);
  if (really_entered)
    scm_leave_guile ();
  return res;
}
