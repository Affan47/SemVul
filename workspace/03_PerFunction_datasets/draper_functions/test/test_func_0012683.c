dfs_post_file_map(opal_buffer_t *bo,
                              orte_dfs_post_callback_fn_t cbfunc,
                              void *cbdata)
{
    orte_dfs_request_t *dfs;

    dfs = OBJ_NEW(orte_dfs_request_t);
    dfs->cmd = ORTE_DFS_POST_CMD;
    dfs->bptr = bo;
    dfs->post_cbfunc = cbfunc;
    dfs->cbdata = cbdata;


    ORTE_DFS_POST_REQUEST(dfs, process_posts);
}
