check_one_component(ompi_communicator_t * comm,
                               const mca_base_component_t * component,
                               mca_coll_base_module_2_0_0_t ** module)
{
    int err;
    int priority = -1;

    err = query(component, comm, &priority, module);

    if (OMPI_SUCCESS == err) {
        priority = (priority < 100) ? priority : 100;
        opal_output_verbose(10, ompi_coll_base_framework.framework_output,
                            "coll:base:comm_select: component available: %s, priority: %d",
                            component->mca_component_name, priority);

    } else {
        priority = -1;
        opal_output_verbose(10, ompi_coll_base_framework.framework_output,
                            "coll:base:comm_select: component not available: %s",
                            component->mca_component_name);
    }

    return priority;
}
