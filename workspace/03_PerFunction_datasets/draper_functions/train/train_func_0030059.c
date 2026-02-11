mca_rcache_base_module_create(const char* name)
{
    mca_base_component_list_item_t* cli;
    mca_rcache_base_component_t* component = NULL;
    mca_rcache_base_module_t* module = NULL;
    mca_rcache_base_selected_module_t *sm;
    bool found = false;

    OPAL_LIST_FOREACH(cli, &ompi_rcache_base_framework.framework_components, mca_base_component_list_item_t) {
         component = (mca_rcache_base_component_t *) cli->cli_component;
         if(0 == strcmp(component->rcache_version.mca_component_name, name)) {
             found = true;
             break;
         }
    }

    if (!found) {
        return NULL;
    }
    module = component->rcache_init();
    sm = OBJ_NEW(mca_rcache_base_selected_module_t);
    sm->rcache_component = component;
    sm->rcache_module = module;
    opal_list_append(&mca_rcache_base_modules, (opal_list_item_t*) sm);
    return module;
}
