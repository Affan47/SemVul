mca_allocator_component_lookup(const char* name)
{

    mca_base_component_list_item_t *cli;
    OPAL_LIST_FOREACH(cli, &ompi_allocator_base_framework.framework_components, mca_base_component_list_item_t) {
         mca_allocator_base_component_t* component = (mca_allocator_base_component_t *) cli->cli_component;
         if(strcmp(component->allocator_version.mca_component_name,
                   name) == 0) {
             return component;
         }
    }
    return NULL;
}
