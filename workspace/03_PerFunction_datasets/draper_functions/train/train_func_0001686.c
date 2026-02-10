rb_f_exit(argc, argv)
    int argc;
    VALUE *argv;
{
    VALUE status;
    int istatus;

    rb_secure(4);
    if (rb_scan_args(argc, argv, "01", &status) == 1) {
	switch (status) {
	  case Qtrue:
	    istatus = EXIT_SUCCESS;
	    break;
	  case Qfalse:
	    istatus = EXIT_FAILURE;
	    break;
	  default:
	    istatus = NUM2INT(status);
#if EXIT_SUCCESS != 0
	    if (istatus == 0) istatus = EXIT_SUCCESS;
#endif
	    break;
	}
    }
    else {
	istatus = EXIT_SUCCESS;
    }
    rb_exit(istatus);
    return Qnil;
}
