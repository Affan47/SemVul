orte_dt_pack_proc(opal_buffer_t *buffer, const void *src,
                      int32_t num_vals, opal_data_type_t type)
{
    int rc;
    int32_t i;
    orte_proc_t **procs;


    procs = (orte_proc_t**) src;

    for (i=0; i < num_vals; i++) {

        if (ORTE_SUCCESS != (rc = opal_dss_pack_buffer(buffer,
                         (void*)(&(procs[i]->name)), 1, ORTE_NAME))) {
            ORTE_ERROR_LOG(rc);
            return rc;
        }


        if (ORTE_SUCCESS != (rc = opal_dss_pack_buffer(buffer,
                         (void*)(&(procs[i]->local_rank)), 1, ORTE_LOCAL_RANK))) {
            ORTE_ERROR_LOG(rc);
            return rc;
        }


        if (ORTE_SUCCESS != (rc = opal_dss_pack_buffer(buffer,
                         (void*)(&(procs[i]->node_rank)), 1, ORTE_NODE_RANK))) {
            ORTE_ERROR_LOG(rc);
            return rc;
        }

#if OPAL_HAVE_HWLOC
        if (ORTE_SUCCESS != (rc = opal_dss_pack_buffer(buffer,
                          (void*)(&procs[i]->cpu_bitmap), 1, OPAL_STRING))) {
        ORTE_ERROR_LOG(rc);
        return rc;
    }
#endif


        if (ORTE_SUCCESS != (rc = opal_dss_pack_buffer(buffer,
                         (void*)(&(procs[i]->state)), 1, ORTE_PROC_STATE))) {
            ORTE_ERROR_LOG(rc);
            return rc;
        }


        if (ORTE_SUCCESS != (rc = opal_dss_pack_buffer(buffer,
                         (void*)(&(procs[i]->app_idx)), 1, ORTE_STD_CNTR))) {
            ORTE_ERROR_LOG(rc);
            return rc;
        }


        if (ORTE_SUCCESS != (rc = opal_dss_pack_buffer(buffer,
                         (void*)&(procs[i]->restarts), 1, OPAL_INT32))) {
            ORTE_ERROR_LOG(rc);
            return rc;
        }

#if OPAL_ENABLE_FT_CR == 1

        if (ORTE_SUCCESS != (rc = opal_dss_pack_buffer(buffer,
                         (void*)(&(procs[i]->ckpt_state)), 1, OPAL_SIZE))) {
            ORTE_ERROR_LOG(rc);
            return rc;
        }


        if (ORTE_SUCCESS != (rc = opal_dss_pack_buffer(buffer,
                         (void*)(&(procs[i]->ckpt_snapshot_ref)), 1, OPAL_STRING))) {
            ORTE_ERROR_LOG(rc);
            return rc;
        }


        if (ORTE_SUCCESS != (rc = opal_dss_pack_buffer(buffer,
                         (void*)(&(procs[i]->ckpt_snapshot_loc)), 1, OPAL_STRING))) {
            ORTE_ERROR_LOG(rc);
            return rc;
        }
#endif
    }

    return ORTE_SUCCESS;
}
