emc_read_command(const int fd) {

    extmon_cmd_t* cmd = NULL;

    {
        uint8_t fixed_part[10];
        if(emc_read_nbytes(fd, 10, fixed_part)
            || strncmp((char*)fixed_part, "CMD:", 4)) {
            log_debug("emc_read_command() failed to read CMD: prefix");
            goto out_error;
        }

        cmd = malloc(sizeof(extmon_cmd_t));
        cmd->idx = ((unsigned)fixed_part[4] << 8) + fixed_part[5];
        cmd->timeout = fixed_part[6];
        cmd->interval = fixed_part[7];
        cmd->args = NULL;
        cmd->num_args = 0;


        const unsigned var_len = ((unsigned)fixed_part[8] << 8) + fixed_part[9];
        if(var_len < 4) {


            log_debug("emc_read_command() variable section too short (%u)!", var_len);
            goto out_error;
        }

        uint8_t var_part[var_len];
        if(emc_read_nbytes(fd, var_len, var_part)) {
            log_debug("emc_read_command() failed to read %u-byte variable section", var_len);
            goto out_error;
        }

        const unsigned n_args = *var_part;
        if(!n_args) {
            log_debug("emc_read_command() got zero-arg command!");
            goto out_error;
        }

        cmd->args = malloc((n_args + 1) * sizeof(char*));
        const uint8_t* current = &var_part[1];
        unsigned len_remain = var_len - 1;
        for(cmd->num_args = 0; cmd->num_args < n_args; cmd->num_args++) {
            const unsigned cmdlen = strnlen((const char*)current, len_remain) + 1;
            cmd->args[cmd->num_args] = malloc(cmdlen);
            if(!nul_within_n_bytes(current, len_remain)) {
                log_debug("emc_read_command(): argument runs off end of buffer");
                goto out_error;
            }
            memcpy((char*)cmd->args[cmd->num_args], current, cmdlen);
            current += cmdlen;
            len_remain -= cmdlen;
        }
        cmd->args[cmd->num_args] = NULL;

        if(!nul_within_n_bytes(current, len_remain)) {
            log_debug("emc_read_command(): argument runs off end of buffer");
            goto out_error;
        }
        cmd->desc = strdup((const char*)current);
        current += strlen((const char*)current);
        current++;

        if(current != (var_part + var_len)) {
            log_debug("emc_read_command(): unused len at end of buffer!");
            goto out_error;
        }
    }

    return cmd;

    out_error:
    if(cmd) {
        if(cmd->args) {
            for(unsigned x = 0; x < cmd->num_args; x++)
                free((char*)cmd->args[x]);
            free(cmd->args);
        }
        free(cmd);
    }
    return NULL;
}
