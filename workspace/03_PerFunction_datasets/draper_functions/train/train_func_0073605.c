main(int argc, char **argv){
    register Argument *arg = Argument_create(argc, argv);
    register gint retval;
    g_log_set_handler(NULL, G_LOG_LEVEL_ERROR|G_LOG_FLAG_FATAL,
                      Argument_error_handler, arg);
    g_assert(Argument_assertion_warning());
    retval = Argument_main(arg);
    Argument_destroy(arg);
    return retval;
    }
