rlock_is_owned(rlockobject *self)
{
    long tid = PyThread_get_thread_ident();

    if (self->rlock_count > 0 && self->rlock_owner == tid) {
        Py_RETURN_TRUE;
    }
    Py_RETURN_FALSE;
}
