orte_filem_base_select(void)
{
    int exit_status = ORTE_SUCCESS;
    orte_filem_base_component_t *best_component = NULL;
    orte_filem_base_module_t *best_module = NULL;


    if( OPAL_SUCCESS != mca_base_select("filem", orte_filem_base_framework.framework_output,
                                        &orte_filem_base_framework.framework_components,
                                        (mca_base_module_t **) &best_module,
                                        (mca_base_component_t **) &best_component) ) {


        return ORTE_SUCCESS;
    }


    orte_filem = *best_module;


    if (NULL != orte_filem.filem_init) {
        if (ORTE_SUCCESS != orte_filem.filem_init()) {
            exit_status = ORTE_ERROR;
        }
    }

    return exit_status;
}
