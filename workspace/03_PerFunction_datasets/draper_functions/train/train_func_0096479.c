Argument_add_cleanup(Argument *arg,
                          Argument_Cleanup_Func cleanup_func,
                          gpointer user_data){
    register Argument_Cleanup *cleanup = g_new(Argument_Cleanup, 1);
    cleanup->cleanup_func = cleanup_func;
    cleanup->user_data = user_data;
    g_ptr_array_add(arg->cleanup_list, cleanup);
    return;
    }
