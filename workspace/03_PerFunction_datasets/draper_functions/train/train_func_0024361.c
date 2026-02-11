dir_s_rmdir(VALUE obj, VALUE dir)
{
    check_dirname(&dir);
    if (rmdir(RSTRING_PTR(dir)) < 0)
	rb_sys_fail_path(dir);

    return INT2FIX(0);
}
