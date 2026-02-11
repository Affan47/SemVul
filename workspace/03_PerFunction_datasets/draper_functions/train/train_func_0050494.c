logging(VMG_ uint argc)
{
    vm_val_t fname_val;
    int log_type;


    check_argc_range(vmg_ argc, 1, 2);


    G_stk->pop(&fname_val);


    log_type = (argc >= 2 ? pop_int_val(vmg0_) : LOG_SCRIPT);


    if (fname_val.typ == VM_NIL)
    {

        switch(log_type)
        {
        case LOG_SCRIPT:
            G_console->close_log_file();
            break;

        case LOG_CMD:
        case LOG_EVENT:
            G_console->close_command_log();
            break;

        default:
            err_throw(VMERR_BAD_VAL_BIF);
        }
    }
    else
    {
        char fname[OSFNMAX];


        G_stk->push(&fname_val);
        pop_str_val_fname(vmg_ fname, sizeof(fname));


        switch(log_type)
        {
        case LOG_SCRIPT:
            G_console->open_log_file(fname);
            break;

        case LOG_CMD:
        case LOG_EVENT:
            G_console->open_command_log(fname, log_type == LOG_EVENT);
            break;

        default:
            err_throw(VMERR_BAD_VAL_BIF);
        }
    }
}
