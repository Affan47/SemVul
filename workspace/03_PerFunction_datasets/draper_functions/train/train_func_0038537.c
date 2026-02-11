ruby_set_argv(int argc, char **argv)
{
    int i;
    VALUE av = rb_argv;

#if defined(USE_DLN_A_OUT)
    if (origarg.argv)
	dln_argv0 = origarg.argv[0];
    else
	dln_argv0 = argv[0];
#endif
    rb_ary_clear(av);
    for (i = 0; i < argc; i++) {
	VALUE arg = rb_external_str_new_cstr(argv[i]);

	OBJ_FREEZE(arg);
	rb_ary_push(av, arg);
    }
}
