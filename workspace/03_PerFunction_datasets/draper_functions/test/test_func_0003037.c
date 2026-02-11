exit_success_p(VALUE exc)
{
    VALUE status_val = rb_attr_get(exc, rb_intern("status"));
    int status;

    if (NIL_P(status_val))
	return Qtrue;
    status = NUM2INT(status_val);
    if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
	return Qtrue;

    return Qfalse;
}
