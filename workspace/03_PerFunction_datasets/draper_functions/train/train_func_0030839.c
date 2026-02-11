ml_coll_hier_bcast_setup(mca_coll_ml_module_t *ml_module)
{

    int ret, i , size_code, alg;
    int topo_index = 0;
    mca_coll_ml_topology_t *topo_info = ml_module->topo_list;

    for (i = 0; i < ML_NUM_MSG; i++) {

        switch (i) {
            case ML_SMALL_MSG:
                size_code = BCAST_SMALL;
                break;
            case ML_LARGE_MSG:
                size_code = BCAST_LARGE;
                break;
            default:
                topo_info->hierarchical_algorithms[ML_BCAST] = NULL;
                return OMPI_ERROR;
        }

        alg = mca_coll_ml_component.coll_config[ML_BCAST][i].algorithm_id;
        topo_index = ml_module->collectives_topology_map[ML_BCAST][alg];
        if (ML_UNDEFINED == alg || ML_UNDEFINED == topo_index) {
            ML_ERROR(("No topology index or algorithm was defined"));
            topo_info->hierarchical_algorithms[ML_BCAST] = NULL;
            return OMPI_ERROR;
        }

        switch (alg) {
            case ML_BCAST_SMALL_DATA_KNOWN:
            case ML_BCAST_LARGE_DATA_KNOWN:
                ret = mca_coll_ml_build_bcast_known_schedule_no_attributes(&topo_info[topo_index],
                        &ml_module->coll_ml_bcast_functions[alg], size_code);
                if (OPAL_UNLIKELY(OMPI_SUCCESS != ret)) {
                    ML_VERBOSE(10, ("Failed to setup static bcast"));
                    topo_info->hierarchical_algorithms[ML_BCAST] = NULL;
                    return ret;
                }
                break;
            case ML_BCAST_SMALL_DATA_UNKNOWN:
            case ML_BCAST_LARGE_DATA_UNKNOWN:
                ret = mca_coll_ml_build_bcast_dynamic_schedule_no_attributes(&topo_info[topo_index],
                        &ml_module->coll_ml_bcast_functions[alg], size_code);
                if (OPAL_UNLIKELY(OMPI_SUCCESS != ret)) {
                    ML_VERBOSE(10, ("Failed to setup dynamic bcast"));
                    topo_info->hierarchical_algorithms[ML_BCAST] = NULL;
                    return ret;
                }
                break;
            case ML_BCAST_SMALL_DATA_SEQUENTIAL:
            case ML_BCAST_LARGE_DATA_SEQUENTIAL:
                ret = mca_coll_ml_build_bcast_sequential_schedule_no_attributes(&topo_info[topo_index],
                        &ml_module->coll_ml_bcast_functions[alg], size_code);
                if (OPAL_UNLIKELY(OMPI_SUCCESS != ret)) {
                    ML_VERBOSE(10, ("Failed to setup static bcast"));
                    topo_info->hierarchical_algorithms[ML_BCAST] = NULL;
                    return ret;
                }
                break;
            default:
                topo_info->hierarchical_algorithms[ML_BCAST] = NULL;
                return OMPI_ERROR;
        }
        assert(NULL != ml_module->coll_ml_bcast_functions[alg] &&
                NULL != ml_module->coll_ml_bcast_functions[alg]);
    }

    topo_info->hierarchical_algorithms[BCOL_BCAST] = NULL;
    return ret;
}
