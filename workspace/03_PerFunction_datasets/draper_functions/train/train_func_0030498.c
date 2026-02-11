check_components(opal_list_t *components)
{
    int priority;
    const mca_base_component_t *component;
    mca_base_component_list_item_t *cli;
    mca_atomic_base_module_1_0_0_t *module;
    opal_list_t *selectable;
    avail_com_t *avail;


    selectable = OBJ_NEW(opal_list_t);


    OPAL_LIST_FOREACH(cli, &oshmem_atomic_base_framework.framework_components, mca_base_component_list_item_t) {
        component = cli->cli_component;

        priority = check_one_component(component, &module);
        if (priority >= 0) {


            avail = OBJ_NEW(avail_com_t);
            avail->ac_priority = priority;
            avail->ac_module = module;

            opal_list_append(selectable, &avail->super);
        }
    }


    if (0 == opal_list_get_size(selectable)) {
        OBJ_RELEASE(selectable);
        return NULL;
    }


    opal_list_sort(selectable, avail_com_compare);


    return selectable;
}
