clish_shell_find_next_completion(const clish_shell_t    *this,
                                 const char             *line,
                                 clish_shell_iterator_t *iter)
{
    const clish_command_t *result=NULL,*cmd1,*cmd2;
    int                    diff;


    cmd1 = clish_view_find_next_completion(this->view,
                                           iter->last_cmd_local,
                                           line);

    cmd2 = clish_view_find_next_completion(this->global,
                                           iter->last_cmd_global,
                                           line);

    diff = clish_command_diff(cmd1,cmd2);
    if(diff > 0)
    {
        result = iter->last_cmd_global = cmd2;
    }
    else
    {
        if(0 == diff)
        {

            iter->last_cmd_global = cmd2;
        }
        result = iter->last_cmd_local = cmd1;
    }
    return result;
}
