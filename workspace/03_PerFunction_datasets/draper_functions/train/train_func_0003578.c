orte_dt_unpack_node(opal_buffer_t *buffer, void *dest,
                        int32_t *num_vals, opal_data_type_t type)
{
    int rc;
    int32_t i, n;
    orte_node_t **nodes;


    nodes = (orte_node_t**) dest;
    for (i=0; i < *num_vals; i++) {


        nodes[i] = OBJ_NEW(orte_node_t);
        if (NULL == nodes[i]) {
            ORTE_ERROR_LOG(ORTE_ERR_OUT_OF_RESOURCE);
            return ORTE_ERR_OUT_OF_RESOURCE;
        }


        n = 1;
        if (ORTE_SUCCESS != (rc = opal_dss_unpack_buffer(buffer,
                         &(nodes[i]->name), &n, OPAL_STRING))) {
            ORTE_ERROR_LOG(rc);
            return rc;
        }


        n = 1;
        if (ORTE_SUCCESS != (rc = opal_dss_unpack_buffer(buffer,
                         (&(nodes[i]->num_procs)), &n, ORTE_VPID))) {
            ORTE_ERROR_LOG(rc);
            return rc;
        }


        n = 1;
        if (ORTE_SUCCESS != (rc = opal_dss_unpack_buffer(buffer,
                         (&(nodes[i]->oversubscribed)), &n, OPAL_BOOL))) {
            ORTE_ERROR_LOG(rc);
            return rc;
        }


        n = 1;
        if (ORTE_SUCCESS != (rc = opal_dss_unpack_buffer(buffer,
                         (&(nodes[i]->state)), &n, ORTE_NODE_STATE))) {
            ORTE_ERROR_LOG(rc);
            return rc;
        }


        n = 1;
        if (ORTE_SUCCESS != (rc = opal_dss_unpack_buffer(buffer,
                         (&(nodes[i]->slots)), &n, ORTE_STD_CNTR))) {
            ORTE_ERROR_LOG(rc);
            return rc;
        }


        if (ORTE_SUCCESS != (rc = opal_dss_unpack_buffer(buffer,
                         (&(nodes[i]->slots_inuse)), &n, ORTE_STD_CNTR))) {
            ORTE_ERROR_LOG(rc);
            return rc;
        }


        if (ORTE_SUCCESS != (rc = opal_dss_unpack_buffer(buffer,
                         (&(nodes[i]->slots)), &n, ORTE_STD_CNTR))) {
            ORTE_ERROR_LOG(rc);
            return rc;
        }


        if (ORTE_SUCCESS != (rc = opal_dss_unpack_buffer(buffer,
                         (&(nodes[i]->slots_max)), &n, ORTE_STD_CNTR))) {
            ORTE_ERROR_LOG(rc);
            return rc;
        }


    }
    return ORTE_SUCCESS;
}
