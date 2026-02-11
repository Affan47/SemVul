pty_check(int argc, VALUE *argv, VALUE self)
{
    VALUE pid, exc;
    pid_t cpid;
    int status;

    rb_scan_args(argc, argv, "11", &pid, &exc);
    cpid = rb_waitpid(NUM2PIDT(pid), &status, WNOHANG|WUNTRACED);
    if (cpid == -1 || cpid == 0) return Qnil;

    if (!RTEST(exc)) return rb_last_status_get();
    raise_from_check(cpid, status);
    return Qnil;
}
