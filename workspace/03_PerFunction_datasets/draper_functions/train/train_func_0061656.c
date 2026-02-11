clish_pargv_new(const clish_command_t *cmd,
                const char            *line,
                size_t                 offset,
                clish_pargv_status_t  *status)
{
    clish_pargv_t *this;
    lub_argv_t   *argv       = lub_argv_new(line,offset);
    unsigned      max_params = lub_argv__get_count(argv);
    unsigned      cmd_params = clish_command__get_param_count(cmd);
    size_t        size;

    if(max_params < cmd_params)
    {
        max_params = cmd_params;
    }


    size = sizeof(clish_parg_t)*(max_params-1) + sizeof(clish_pargv_t);

    this = malloc(size);

    if(NULL != this)
    {
        *status = clish_pargv_init(this,cmd,argv);
        switch(*status)
        {
            case clish_LINE_OK:
                break;
            case clish_BAD_CMD:
            case clish_BAD_PARAM:
            case clish_BAD_HISTORY:

                clish_pargv_delete(this);
                this = NULL;
                break;
        }
    }


    lub_argv_delete(argv);

    return this;
}
