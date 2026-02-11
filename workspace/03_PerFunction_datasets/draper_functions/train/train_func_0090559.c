query(const mca_base_component_t * component,
                 oshmem_group_t *group,
                 int *priority,
                 mca_scoll_base_module_1_0_0_t **module)
{
    *module = NULL;
    if (1 == component->mca_type_major_version
            && 0 == component->mca_type_minor_version
            && 0 == component->mca_type_release_version) {
        const mca_scoll_base_component_1_0_0_t *coll100 =
                (mca_scoll_base_component_1_0_0_t *) component;

        return query_1_0_0(coll100, group, priority, module);
    }


    return OSHMEM_ERROR;
}
