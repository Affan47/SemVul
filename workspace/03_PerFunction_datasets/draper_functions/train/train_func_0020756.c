_entryrdn_open_index(backend *be, struct attrinfo **ai, DB **dbp)
{
    int rc = -1;
    ldbm_instance *inst = NULL;

    if (NULL == be || NULL == ai || NULL == dbp) {
        slapi_log_error(SLAPI_LOG_FATAL, ENTRYRDN_TAG,
                        "_entryrdn_open_index: Param error: Empty %s\n",
                        NULL==be?"be":NULL==ai?"attrinfo container":
                        NULL==dbp?"db container":"unknown");
        goto bail;
    }
    *ai = NULL;
    *dbp = NULL;

    ainfo_get(be, LDBM_ENTRYRDN_STR, ai);
    if (NULL == *ai) {
        rc = ENODATA;
        goto bail;
    }
    inst = (ldbm_instance *)be->be_instance_info;
    if ((*ai)->ai_attrcrypt && entryrdn_warning_on_encryption) {
        slapi_log_error(SLAPI_LOG_FATAL, ENTRYRDN_TAG,
                        "Encrypting entryrdn is not supported.  "
                        "Ignoring the configuration entry \"dn: "
                        "cn=entryrdn, cn=encrypted attributes, cn=<backend>, "
                        "cn=%s, cn=plugins, cn=config\"\n",
                        inst->inst_li->li_plugin->plg_name);

        entryrdn_warning_on_encryption = 0;
    }
    rc = dblayer_get_index_file(be, *ai, dbp, DBOPEN_CREATE);
bail:
    return rc;
}
