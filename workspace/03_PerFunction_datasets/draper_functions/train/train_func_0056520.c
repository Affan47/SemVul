globus_i_gfs_config_get(
    const char *                        option_name)
{
    globus_l_gfs_config_option_t *      option;
    void *                              value = NULL;
    GlobusGFSName(globus_i_gfs_config_get);
    GlobusGFSDebugEnter();

    option = (globus_l_gfs_config_option_t *)
        globus_hashtable_lookup(&option_table, (void *) option_name);

    if(option && option->value)
    {
        value = option->value;
    }

    GlobusGFSDebugExit();
    return value;
}
