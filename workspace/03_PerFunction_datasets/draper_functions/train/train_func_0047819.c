gss_krb5_export_lucid_sec_context(OM_uint32 *minor_status,
                                  gss_ctx_id_t *context_handle,
                                  OM_uint32 version,
                                  void **kctx)
{
    unsigned char oid_buf[GSS_KRB5_EXPORT_LUCID_SEC_CONTEXT_OID_LENGTH + 6];
    gss_OID_desc req_oid;
    OM_uint32 major_status, minor;
    gss_buffer_set_t data_set = GSS_C_NO_BUFFER_SET;

    if (kctx == NULL)
        return GSS_S_CALL_INACCESSIBLE_WRITE;

    *kctx = NULL;

    req_oid.elements = oid_buf;
    req_oid.length = sizeof(oid_buf);

    major_status = generic_gss_oid_compose(minor_status,
                                           GSS_KRB5_EXPORT_LUCID_SEC_CONTEXT_OID,
                                           GSS_KRB5_EXPORT_LUCID_SEC_CONTEXT_OID_LENGTH,
                                           (int)version,
                                           &req_oid);
    if (GSS_ERROR(major_status))
        return major_status;

    major_status = gss_inquire_sec_context_by_oid(minor_status,
                                                  *context_handle,
                                                  &req_oid,
                                                  &data_set);
    if (GSS_ERROR(major_status))
        return major_status;

    if (data_set == GSS_C_NO_BUFFER_SET ||
        data_set->count != 1 ||
        data_set->elements[0].length != sizeof(void *)) {
        *minor_status = EINVAL;
        return GSS_S_FAILURE;
    }

    *kctx = *((void **)data_set->elements[0].value);


    (void)gss_delete_sec_context(minor_status, context_handle, NULL);
    *context_handle = GSS_C_NO_CONTEXT;

    generic_gss_release_buffer_set(&minor, &data_set);

    return GSS_S_COMPLETE;
}
