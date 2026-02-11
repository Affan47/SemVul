gsskrb5_extract_authz_data_from_sec_context(OM_uint32 *minor_status,
                                            const gss_ctx_id_t context_handle,
                                            int ad_type,
                                            gss_buffer_t ad_data)
{
    gss_OID_desc req_oid;
    unsigned char oid_buf[GSS_KRB5_EXTRACT_AUTHZ_DATA_FROM_SEC_CONTEXT_OID_LENGTH + 6];
    OM_uint32 major_status;
    gss_buffer_set_t data_set = GSS_C_NO_BUFFER_SET;

    if (ad_data == NULL)
        return GSS_S_CALL_INACCESSIBLE_WRITE;

    req_oid.elements = oid_buf;
    req_oid.length = sizeof(oid_buf);

    major_status = generic_gss_oid_compose(minor_status,
                                           GSS_KRB5_EXTRACT_AUTHZ_DATA_FROM_SEC_CONTEXT_OID,
                                           GSS_KRB5_EXTRACT_AUTHZ_DATA_FROM_SEC_CONTEXT_OID_LENGTH,
                                           ad_type,
                                           &req_oid);
    if (GSS_ERROR(major_status))
        return major_status;

    major_status = gss_inquire_sec_context_by_oid(minor_status,
                                                  context_handle,
                                                  (gss_OID)&req_oid,
                                                  &data_set);
    if (major_status != GSS_S_COMPLETE) {
        return major_status;
    }

    if (data_set == GSS_C_NO_BUFFER_SET ||
        data_set->count != 1) {
        return GSS_S_FAILURE;
    }

    ad_data->length = data_set->elements[0].length;
    ad_data->value = data_set->elements[0].value;

    data_set->elements[0].length = 0;
    data_set->elements[0].value = NULL;

    data_set->count = 0;

    gss_release_buffer_set(minor_status, &data_set);

    return GSS_S_COMPLETE;
}
