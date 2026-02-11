emc_write_command(const int fd, const extmon_cmd_t* cmd) {
    unsigned alloc = 256;
    unsigned len = 0;
    char* buf = malloc(alloc);


    memcpy(buf, "CMD:", 4);
    len += 4;


    buf[len++] = cmd->idx >> 8;
    buf[len++] = cmd->idx & 0xFF;
    buf[len++] = cmd->timeout;
    buf[len++] = cmd->interval;


    len += 2;


    buf[len++] = cmd->num_args;
    for(unsigned i = 0; i < cmd->num_args; i++) {
        const unsigned arg_len = strlen(cmd->args[i]) + 1;
        while((len + arg_len + 16) > alloc) {
            alloc *= 2;
            buf = realloc(buf, alloc);
        }
        memcpy(&buf[len], cmd->args[i], arg_len);
        len += arg_len;
    }


    const unsigned desc_len = strlen(cmd->desc) + 1;
    while((len + desc_len + 16) > alloc) {
        alloc *= 2;
        buf = realloc(buf, alloc);
    }
    memcpy(&buf[len], cmd->desc, desc_len);
    len += desc_len;


    const unsigned var_len = len - 10;
    buf[8] = var_len >> 8;
    buf[9] = var_len & 0xFF;

    bool rv = emc_write_string(fd, buf, len);
    free(buf);
    return rv;
}
