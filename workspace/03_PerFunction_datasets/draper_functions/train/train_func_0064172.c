banner_goto(VMG_ uint argc)
{
    int id;
    void *hdl;
    CVmConsole *console;
    int row, col;


    check_argc(vmg_ argc, 3);


    id = pop_int_val(vmg0_);


    row = pop_int_val(vmg0_);
    col = pop_int_val(vmg0_);


    if (row < 1 || col < 1)
        err_throw(VMERR_BAD_VAL_BIF);


    hdl = G_console->get_banner_manager()->get_os_handle(id);
    console = G_console->get_banner_manager()->get_console(id);
    if (hdl == 0 || console == 0)
        err_throw(VMERR_BAD_VAL_BIF);


    console->flush(vmg_ VM_NL_NONE);
    console->empty_buffers(vmg0_);


    os_banner_goto(hdl, row - 1, col - 1);
}
