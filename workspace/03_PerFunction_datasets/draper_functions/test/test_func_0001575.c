init_cib_cache_cb(xmlNode * msg, int call_id, int rc, xmlNode * output, void *user_data)
{
    crm_info("Updating device list from the cib: init");
    have_cib_devices = TRUE;
    local_cib = copy_xml(output);

    fencing_topology_init(msg);
    cib_devices_update();
}
