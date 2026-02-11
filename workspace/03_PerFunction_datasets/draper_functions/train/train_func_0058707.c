gfs_l_gfork_opts_mem_size(
    globus_options_handle_t             opts_handle,
    char *                              cmd,
    char **                             opt,
    void *                              arg,
    int *                               out_parms_used)
{
    globus_result_t                     result;
    globus_off_t                        val;

    result = gfs_l_gfork_opts_kmgint(opt[0], &val);
    if(result != GLOBUS_SUCCESS)
    {
        goto error;
    }

    gfs_l_memlimiting = GLOBUS_TRUE;
    gfs_l_memlimit_available = val;
    gfs_l_memlimit = val;

    return GLOBUS_SUCCESS;
error:
    return result;
}
