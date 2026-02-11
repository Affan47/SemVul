mca_atomic_base_close(void)
{
    mca_base_component_list_item_t *cli, *next;
    const mca_base_component_t *component;

    OPAL_LIST_FOREACH_SAFE(cli, next, &oshmem_atomic_base_framework.framework_components, mca_base_component_list_item_t) {
        component = cli->cli_component;
        mca_atomic_base_component_t *atomic =
                (mca_atomic_base_component_t *) component;

        if (NULL != atomic->atomic_finalize) {
            atomic->atomic_finalize();
        }
    }


    return mca_base_framework_components_close(&oshmem_atomic_base_framework, NULL);
}
