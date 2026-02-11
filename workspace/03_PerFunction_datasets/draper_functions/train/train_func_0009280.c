hasObjectClass(Slapi_Entry *entry, const char *objectClass)
{
    int rc = 0;
    int i;
    Slapi_Attr  *obj_attr = NULL;
    Slapi_Value *value    = NULL;

    rc = slapi_entry_attr_find(entry, "objectclass", &obj_attr);

    if (rc != 0) {
        return 0;
    }

    slapi_log_error(SLAPI_LOG_PLUGIN, POSIX_WINSYNC_PLUGIN_NAME,
                    "Scanning objectclasses\n");

    for (
        i = slapi_attr_first_value(obj_attr, &value);
        i != -1;
        i = slapi_attr_next_value(obj_attr, i, &value)
    ) {
        const char *oc = NULL;
        oc = slapi_value_get_string(value);
        if (strcasecmp(oc, objectClass) == 0) {
            return 1;
        }
    }

    return 0;
}
