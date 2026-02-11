globus_gfs_log_result(
    globus_gfs_log_type_t               type,
    const char *                        lead,
    globus_result_t                     result)
{
    char *                              message;
    GlobusGFSName(globus_gfs_log_result);
    GlobusGFSDebugEnter();

    if(result != GLOBUS_SUCCESS)
    {
        message = globus_error_print_friendly(globus_error_peek(result));
    }
    else
    {
        message = globus_libc_strdup("(unknown error)");
    }
    globus_gfs_log_message(type, "%s:\n%s\n", lead, message);
    globus_free(message);

    GlobusGFSDebugExit();
}
