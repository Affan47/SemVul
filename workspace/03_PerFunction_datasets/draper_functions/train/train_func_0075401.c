gzfile_wrap(int argc, VALUE *argv, VALUE klass, int close_io_on_error)
{
    VALUE obj;

    if (close_io_on_error) {
	int state = 0;
	new_wrap_arg_t arg;
	arg.argc = argc;
	arg.argv = argv;
	arg.klass = klass;
	obj = rb_protect(new_wrap, (VALUE)&arg, &state);
	if (state) {
	    rb_io_close(argv[0]);
	    rb_jump_tag(state);
	}
    }
    else {
	obj = rb_class_new_instance(argc, argv, klass);
    }

    if (rb_block_given_p()) {
	return rb_ensure(rb_yield, obj, gzfile_ensure_close, obj);
    }
    else {
	return obj;
    }
}
