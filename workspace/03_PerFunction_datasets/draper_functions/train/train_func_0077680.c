init(
    const char* name, int& argc, char** argv,
    const OptionDesc* opts, const PropertyData* initprops, Display* display
) {
    argc_ = argc;
    argv_ = new char*[argc + 1];
    for (int i = 0; i < argc; i++) {
	argv_[i] = argv[i];
    }
    argv_[argc_] = nil;

    init_style(name, initprops);
    if (opts != nil) {
	parse_args(argc, argv, opts);
    }
    parse_args(argc, argv, defoptions);
    init_display(display);

    Cursor::init();

#ifdef sgi
    if (style_->value_is_on("malloc_debug")) {
	mallopt(M_DEBUG, 1);
    }
#endif
}
