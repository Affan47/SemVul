close_printer(void)
{
#ifndef _WINDOWS
    if(trailer){
	if(*trailer)
	  fputs(trailer, ps_global->print->fp);

	fs_give((void **)&trailer);
    }

    if(ps_global->print->fp == stdout) {
	if(ansi_off)
          fputs("\033[4i", stdout);
	else
	  printf("%c", 20);

        fflush(stdout);
	if(F_OFF(F_PRESERVE_START_STOP, ps_global))
	  xonxoff_proc(0);

	crlf_proc(0);
    } else {
	(void) close_system_pipe(&ps_global->print->pipe, NULL, pipe_callback);
	display_output_file(ps_global->print->result, "PRINT", NULL, 1);
	if(ps_global->print && ps_global->print->result)
	  fs_give((void **) &ps_global->print->result);
    }
#else
    mswin_print_done();
#endif

    if(ps_global->print)
      fs_give((void **) &ps_global->print);

    q_status_message(SM_ASYNC, 0, 3, "Print command completed");
    display_message('x');
}
