pst_wtermsig(VALUE st)
{
    int status = PST2INT(st);

    if (WIFSIGNALED(status))
	return INT2NUM(WTERMSIG(status));
    return Qnil;
}
