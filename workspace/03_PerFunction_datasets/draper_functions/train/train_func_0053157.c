send_complete(char *file, int status)
{
    opal_buffer_t *buf;
    int rc;

    buf = OBJ_NEW(opal_buffer_t);
    if (OPAL_SUCCESS != (rc = opal_dss.pack(buf, &file, 1, OPAL_STRING))) {
        ORTE_ERROR_LOG(rc);
        OBJ_RELEASE(buf);
        return;
    }
    if (OPAL_SUCCESS != (rc = opal_dss.pack(buf, &status, 1, OPAL_INT))) {
        ORTE_ERROR_LOG(rc);
        OBJ_RELEASE(buf);
        return;
    }
    if (0 > (rc = orte_rml.send_buffer_nb(ORTE_PROC_MY_HNP, buf,
                                          ORTE_RML_TAG_FILEM_BASE_RESP,
                                          orte_rml_send_callback, NULL))) {
        ORTE_ERROR_LOG(rc);
        OBJ_RELEASE(buf);
    }
}
