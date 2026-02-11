thread_wakeup(value thread)
{
  caml_thread_t th = (caml_thread_t) thread;
  switch (th->status) {
  case SUSPENDED:
    th->status = RUNNABLE;
    Assign(th->retval, RESUMED_WAKEUP);
    break;
  case KILLED:
    failwith("Thread.wakeup: killed thread");
  default:
    failwith("Thread.wakeup: thread not suspended");
  }
  return Val_unit;
}
