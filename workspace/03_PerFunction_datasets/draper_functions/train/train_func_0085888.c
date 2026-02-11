SCPI_IsCmd(scpi_t * context, const char * cmd) {
    if (!context->param_list.cmd) {
        return FALSE;
    }

    const char * pattern = context->param_list.cmd->pattern;
    return matchCommand(pattern, cmd, strlen(cmd));
}
