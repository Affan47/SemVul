rb_thread_keys(VALUE self)
{
    rb_thread_t *th;
    VALUE ary = rb_ary_new();
    GetThreadPtr(self, th);

    if (th->local_storage) {
	st_foreach(th->local_storage, thread_keys_i, ary);
    }
    return ary;
}
