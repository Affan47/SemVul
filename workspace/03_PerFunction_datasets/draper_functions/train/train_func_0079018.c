rb_fiber_reset_root_local_storage(VALUE thval)
{
    rb_thread_t *th;
    rb_fiber_t	*fib;

    GetThreadPtr(thval, th);
    if (th->root_fiber && th->root_fiber != th->fiber) {
	GetFiberPtr(th->root_fiber, fib);
	th->local_storage = fib->cont.saved_thread.local_storage;
    }
}
