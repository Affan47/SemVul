get_action_timeout(stonith_device_t * device, const char *action, int default_timeout)
{
    char buffer[512] = { 0, };
    char *value = NULL;

    CRM_CHECK(action != NULL, return default_timeout);

    if (!device->params) {
        return default_timeout;
    }

    snprintf(buffer, sizeof(buffer) - 1, "pcmk_%s_timeout", action);
    value = g_hash_table_lookup(device->params, buffer);

    if (!value) {
        return default_timeout;
    }

    return atoi(value);
}
