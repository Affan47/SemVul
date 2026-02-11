cpl_msg_stop(void)
{
    if (msg_init == 0)
        return;

#ifdef CPL_HAVE_STREAM_DUPLICATION
#ifdef CPL_HAVE_WINDOW_RESIZING
    if (act.sa_handler == _cpl_change_width)
        sigaction(SIGWINCH, &oact, NULL);
#endif
#endif

    cx_print_set_handler(default_printer);
    cx_printerr_set_handler(default_error);

    if (msg_stdout != stdout)
        fclose(msg_stdout);

    if (msg_stderr != stderr)
        fclose(msg_stderr);

    cpl_msg_stop_log();

    msg_init = 0;
}
