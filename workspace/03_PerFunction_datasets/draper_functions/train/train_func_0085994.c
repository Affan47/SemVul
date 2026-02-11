globus_l_gfs_ipc_unpack_command(
    globus_i_gfs_ipc_handle_t *         ipc,
    globus_byte_t *                     buffer,
    globus_size_t                       len)
{
    globus_gfs_command_info_t *         cmd_info;
    int                                 argc;
    int                                 ctr;
    GlobusGFSName(globus_l_gfs_ipc_unpack_command);
    GlobusGFSDebugEnter();

    cmd_info = (globus_gfs_command_info_t *)
        globus_calloc(1, sizeof(globus_gfs_command_info_t));
    if(cmd_info == NULL)
    {
        goto error;
    }

    GFSDecodeUInt32(buffer, len, cmd_info->command);
    GFSDecodeString(buffer, len, cmd_info->pathname);
    GFSDecodeUInt64(buffer, len, cmd_info->cksm_offset);
    GFSDecodeUInt64(buffer, len, cmd_info->cksm_length);
    GFSDecodeString(buffer, len, cmd_info->cksm_alg);
    GFSDecodeUInt32(buffer, len, cmd_info->chmod_mode);
    GFSDecodeUInt32(buffer, len, cmd_info->utime_time);
    GFSDecodeString(buffer, len, cmd_info->chgrp_group);
    GFSDecodeString(buffer, len, cmd_info->from_pathname);
    GFSDecodeString(buffer, len, cmd_info->authz_assert);
    GFSDecodeUInt32(buffer, len, argc);
    if(argc > 0)
    {
        cmd_info->op_info =
            globus_calloc(1, sizeof(globus_i_gfs_op_info_t));
        cmd_info->op_info->argc = argc;
        cmd_info->op_info->argv = globus_calloc(argc, sizeof(char *));
        for(ctr = 0; ctr < cmd_info->op_info->argc; ctr++)
        {
            GFSDecodeString(buffer, len, cmd_info->op_info->argv[ctr]);
        }
    }

    GlobusGFSDebugExit();
    return cmd_info;

decode_err:
    globus_free(cmd_info);
error:
    GlobusGFSDebugExitWithError();
    return NULL;
}
