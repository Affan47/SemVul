globus_gfs_brain_select_nodes(
    globus_i_gfs_brain_node_t ***       out_nodes,
    int *                               out_array_length,
    const char *                        repo_name,
    globus_off_t                        filesize,
    int                                 min_count,
    int                                 max_count)
{
    globus_result_t                     result;
    GlobusGFSName(globus_gfs_brain_select_nodes);

    if(brain_l_module != NULL && brain_l_module->select_func != NULL)
    {
        result = brain_l_module->select_func(
            out_nodes,
            out_array_length,
            repo_name,
            filesize,
            min_count,
            max_count);
        if(result != GLOBUS_SUCCESS)
        {
            goto error;
        }
    }

    return GLOBUS_SUCCESS;

error:
    return result;
}
