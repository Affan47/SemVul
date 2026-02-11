register_module(const DAQ_Module_t *dm, void *dl_handle)
{
    DAQ_ListNode_t *node;


    if (dm->api_version != DAQ_API_VERSION)
    {
        fprintf(stderr, "%s: Module API version (0x%x) differs from expected version (0x%x)\n",
                dm->name, dm->api_version, DAQ_API_VERSION);
        return DAQ_ERROR;
    }


    if (!dm->initialize || !dm->set_filter || !dm->start || !dm->acquire || !dm->inject || !dm->breakloop ||
        !dm->stop || !dm->shutdown || !dm->check_status || !dm->get_stats || !dm->reset_stats ||
        !dm->get_snaplen || !dm->get_capabilities || !dm->get_errbuf || !dm->set_errbuf || !dm->get_device_index)
    {
        fprintf(stderr, "%s: Module definition is missing function pointer(s)!\n", dm->name);
        return DAQ_ERROR;
    }


    for (node = module_list; node; node = node->next)
    {
        if (!strcmp(node->module->name, dm->name))
            break;
    }


    if (node)
    {
        if (node->module->module_version >= dm->module_version)
        {
            DEBUG("DAQ module with name '%s' was already loaded with version %u (versus %u)!\n",
                    node->module->name, node->module->module_version, dm->module_version);
            return DAQ_ERROR_EXISTS;
        }
        if (node->dl_handle)
        {
            dlclose(node->dl_handle);
        }
    }
    else
    {
        node = calloc(1, sizeof(DAQ_ListNode_t));
        if (!node)
            return DAQ_ERROR_NOMEM;
        node->next = module_list;
        module_list = node;
        num_modules++;
    }

    DEBUG("Registered daq module: %s\n", dm->name);
    node->module = dm;
    node->dl_handle = dl_handle;

    return DAQ_SUCCESS;
}
