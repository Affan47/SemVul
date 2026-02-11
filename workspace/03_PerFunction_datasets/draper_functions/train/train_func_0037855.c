usn_start(Slapi_PBlock *pb)
{
    int rc = SLAPI_PLUGIN_SUCCESS;
    Slapi_Value *value;

    slapi_log_error(SLAPI_LOG_TRACE, USN_PLUGIN_SUBSYSTEM, "--> usn_start\n");

    rc = usn_rootdse_init();
    rc |= usn_cleanup_start(pb);
    if (rc) {
        rc = SLAPI_PLUGIN_FAILURE;
        goto bail;
    }
    if (0) {
        Slapi_ValueSet *vs = NULL;
        Slapi_Value *v = NULL;
        int i;

        slapi_get_plugin_default_config("nsds5ReplicatedAttributeList", &vs);
        if (vs) {
            for (i = slapi_valueset_first_value(vs, &v);
                 i != -1;
                 i = slapi_valueset_next_value(vs, i, &v)) {
                slapi_log_error(SLAPI_LOG_FATAL, USN_PLUGIN_SUBSYSTEM,
                        "nsds5ReplicatedAttributeList: %s\n",
                        slapi_value_get_string(v));
            }
        }
        slapi_valueset_free(vs);
    }


    value = slapi_value_new_string("(objectclass=*) $ EXCLUDE entryusn");
    if (slapi_set_plugin_default_config("nsds5ReplicatedAttributeList", value)) {
        rc = SLAPI_PLUGIN_FAILURE;
    }
    slapi_value_free(&value);
    g_plugin_started = 1;
bail:
    slapi_log_error(SLAPI_LOG_TRACE, USN_PLUGIN_SUBSYSTEM,
                    "<-- usn_start (rc: %d)\n", rc);
    return rc;
}
