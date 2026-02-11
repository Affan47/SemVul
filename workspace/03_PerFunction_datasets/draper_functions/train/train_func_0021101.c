build_device_from_xml(xmlNode * msg)
{
    const char *value = NULL;
    xmlNode *dev = get_xpath_object("//" F_STONITH_DEVICE, msg, LOG_ERR);
    stonith_device_t *device = NULL;

    device = calloc(1, sizeof(stonith_device_t));
    device->id = crm_element_value_copy(dev, XML_ATTR_ID);
    device->agent = crm_element_value_copy(dev, "agent");
    device->namespace = crm_element_value_copy(dev, "namespace");
    device->params = xml2list(dev);

    value = g_hash_table_lookup(device->params, STONITH_ATTR_HOSTLIST);
    if (value) {
        device->targets = parse_host_list(value);
    }

    value = g_hash_table_lookup(device->params, STONITH_ATTR_HOSTMAP);
    device->aliases = build_port_aliases(value, &(device->targets));

    device->agent_metadata = get_agent_metadata(device->agent);
    device->on_target_actions = get_on_target_actions(device->agent_metadata);

    value = g_hash_table_lookup(device->params, "nodeid");
    if (!value) {
        device->include_nodeid = is_nodeid_required(device->agent_metadata);
    }

    if (device->on_target_actions) {
        crm_info("The fencing device '%s' requires actions (%s) to be executed on the target node",
                 device->id, device->on_target_actions);
    }

    device->work = mainloop_add_trigger(G_PRIORITY_HIGH, stonith_device_dispatch, device);


    return device;
}
