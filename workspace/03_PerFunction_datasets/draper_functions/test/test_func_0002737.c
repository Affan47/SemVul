check_internal(const char *command)  {
    AWTI_EXPORT_CMD cmd = AWTI_EXPORT_INVALID;
    for (int i = 0; internal_export_commands[i]; ++i) {
        if (strcmp(command, internal_export_commands[i]) == 0) {
            cmd = static_cast<AWTI_EXPORT_CMD>(i);
        }
    }
    return cmd;
}
