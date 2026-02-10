ap_set_file_slot(cmd_parms *cmd, void *struct_ptr,
                                                 const char *arg)
{


    const char *path;
    int offset = (int)(long)cmd->info;

    path = ap_server_root_relative(cmd->pool, arg);

    if (!path) {
        return apr_pstrcat(cmd->pool, "Invalid file path ",
                           arg, NULL);
    }

    *(const char **) ((char*)struct_ptr + offset) = path;

    return NULL;
}
