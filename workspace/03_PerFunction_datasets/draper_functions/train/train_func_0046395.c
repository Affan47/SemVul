proc_seteuid(VALUE obj, VALUE euid)
{
    rb_uid_t uid;

    check_uid_switch();

    uid = NUM2UIDT(euid);
#if defined(HAVE_SETRESUID)
    if (setresuid(-1, uid, -1) < 0) rb_sys_fail(0);
#elif defined HAVE_SETREUID
    if (setreuid(-1, uid) < 0) rb_sys_fail(0);
#elif defined HAVE_SETEUID
    if (seteuid(uid) < 0) rb_sys_fail(0);
#elif defined HAVE_SETUID
    if (uid == getuid()) {
	if (setuid(uid) < 0) rb_sys_fail(0);
    }
    else {
	rb_notimplement();
    }
#else
    rb_notimplement();
#endif
    return euid;
}
