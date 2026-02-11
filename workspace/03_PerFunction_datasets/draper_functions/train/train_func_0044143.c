orte_dt_copy_map(orte_job_map_t **dest, orte_job_map_t *src, opal_data_type_t type)
{
    orte_std_cntr_t i;

    if (NULL == src) {
        *dest = NULL;
        return ORTE_SUCCESS;
    }


    *dest = OBJ_NEW(orte_job_map_t);
    if (NULL == *dest) {
        ORTE_ERROR_LOG(ORTE_ERR_OUT_OF_RESOURCE);
        return ORTE_ERR_OUT_OF_RESOURCE;
    }


    (*dest)->mapping = src->mapping;
    (*dest)->ranking = src->ranking;
#if OPAL_HAVE_HWLOC
    (*dest)->binding = src->binding;
#endif
    if (NULL != src->ppr) {
        (*dest)->ppr = strdup(src->ppr);
    }
    (*dest)->display_map = src->display_map;
    (*dest)->num_new_daemons = src->num_new_daemons;
    (*dest)->daemon_vpid_start = src->daemon_vpid_start;
    (*dest)->num_nodes = src->num_nodes;


    (*dest)->nodes->lowest_free = src->nodes->lowest_free;
    (*dest)->nodes->number_free = src->nodes->number_free;
    (*dest)->nodes->size = src->nodes->size;
    (*dest)->nodes->max_size = src->nodes->max_size;
    (*dest)->nodes->block_size = src->nodes->block_size;
    for (i=0; i < src->nodes->size; i++) {
        (*dest)->nodes->addr[i] = src->nodes->addr[i];
    }

    return ORTE_SUCCESS;
}
