process_getfm(int fd, short args, void *cbdata)
{
    orte_dfs_request_t *dfs = (orte_dfs_request_t*)cbdata;
    orte_dfs_jobfm_t *jfm;
    opal_list_item_t *item;
    opal_buffer_t xfer;
    int32_t n, ntotal;
    int rc;


    ntotal = 0;
    n = -1;
    for (item = opal_list_get_first(&file_maps);
         item != opal_list_get_end(&file_maps);
         item = opal_list_get_next(item)) {
        jfm = (orte_dfs_jobfm_t*)item;
        if (ORTE_JOBID_WILDCARD == dfs->target.jobid ||
            jfm->jobid == dfs->target.jobid) {
            n = get_job_maps(jfm, dfs->target.vpid, &dfs->bucket);
            if (n < 0) {
                break;
            }
            ntotal += n;
        }
    }

    if (n < 0) {

        if (NULL != dfs->fm_cbfunc) {
            dfs->fm_cbfunc(NULL, dfs->cbdata);
        }
    } else {
        OBJ_CONSTRUCT(&xfer, opal_buffer_t);
        if (OPAL_SUCCESS != (rc = opal_dss.pack(&xfer, &ntotal, 1, OPAL_INT32))) {
            ORTE_ERROR_LOG(rc);
            OBJ_DESTRUCT(&xfer);
            if (NULL != dfs->fm_cbfunc) {
                dfs->fm_cbfunc(NULL, dfs->cbdata);
            }
            return;
        }
        opal_dss.copy_payload(&xfer, &dfs->bucket);

        if (NULL != dfs->fm_cbfunc) {
            dfs->fm_cbfunc(&xfer, dfs->cbdata);
        }
        OBJ_DESTRUCT(&xfer);
    }
    OBJ_RELEASE(dfs);
}
