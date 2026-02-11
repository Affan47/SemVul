modperl_handler_new(apr_pool_t *p, const char *name)
{
    modperl_handler_t *handler =
        (modperl_handler_t *)apr_pcalloc(p, sizeof(*handler));

    switch (*name) {
      case '+':
        ++name;
        MpHandlerAUTOLOAD_On(handler);
        break;
      case '-':
        ++name;


        MpHandlerAUTOLOAD_Off(handler);
        break;
    }


    handler->name = name;
    MP_TRACE_h(MP_FUNC, "[%s] new handler %s",
               modperl_pid_tid(p), handler->name);

    return handler;
}
