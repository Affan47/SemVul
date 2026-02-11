opal_cmd_line_get_param(opal_cmd_line_t *cmd, const char *opt, int inst,
                              int idx)
{
    int num_found;
    opal_list_item_t *item;
    cmd_line_param_t *param;
    cmd_line_option_t *option;


    opal_mutex_lock(&cmd->lcl_mutex);


    num_found = 0;
    option = find_option(cmd, opt);
    if (NULL != option) {


        if (idx < option->clo_num_params) {
            for (item = opal_list_get_first(&cmd->lcl_params);
                 opal_list_get_end(&cmd->lcl_params) != item;
                 item = opal_list_get_next(item)) {
                param = (cmd_line_param_t *) item;
                if (param->clp_option == option) {
                    if (num_found == inst) {
                        opal_mutex_unlock(&cmd->lcl_mutex);
                        return param->clp_argv[idx];
                    }
                    ++num_found;
                }
            }
        }
    }


    opal_mutex_unlock(&cmd->lcl_mutex);


    return NULL;
}
