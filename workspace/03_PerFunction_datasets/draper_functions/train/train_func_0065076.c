dfs_purge_file_maps(orte_jobid_t jobid,
                                orte_dfs_purge_callback_fn_t cbfunc,
                                void *cbdata)
{
    orte_dfs_request_t *dfs;

    opal_output_verbose(1, orte_dfs_base_framework.framework_output,
                        "%s purging file maps for job %s",
                        ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                        ORTE_JOBID_PRINT(jobid));

    dfs = OBJ_NEW(orte_dfs_request_t);
    dfs->cmd = ORTE_DFS_PURGE_CMD;
    dfs->target.jobid = jobid;
    dfs->purge_cbfunc = cbfunc;
    dfs->cbdata = cbdata;


    ORTE_DFS_POST_REQUEST(dfs, process_purge);
}
