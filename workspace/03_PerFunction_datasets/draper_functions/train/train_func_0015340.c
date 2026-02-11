gss_get_name_attribute(OM_uint32 *minor_status,
                       gss_name_t name,
                       gss_buffer_t attr,
                       int *authenticated,
                       int *complete,
                       gss_buffer_t value,
                       gss_buffer_t display_value,
                       int *more)
{
    OM_uint32           status;
    gss_union_name_t    union_name;
    gss_mechanism       mech;

    if (minor_status == NULL)
        return GSS_S_CALL_INACCESSIBLE_WRITE;

    if (name == GSS_C_NO_NAME)
        return GSS_S_CALL_INACCESSIBLE_READ | GSS_S_BAD_NAME;
    if (attr == GSS_C_NO_BUFFER)
        return GSS_S_CALL_INACCESSIBLE_READ;
    if (more == NULL)
        return GSS_S_CALL_INACCESSIBLE_WRITE;

    if (authenticated != NULL)
        *authenticated = 0;
    if (complete != NULL)
        *complete = 0;
    if (value != GSS_C_NO_BUFFER) {
        value->value = NULL;
        value->length = 0;
    }
    if (display_value != GSS_C_NO_BUFFER) {
        display_value->value = NULL;
        display_value->length = 0;
    }

    *minor_status = 0;

    union_name = (gss_union_name_t)name;

    if (union_name->mech_type == GSS_C_NO_OID)
        return GSS_S_UNAVAILABLE;

    mech = gssint_get_mechanism(name->mech_type);
    if (mech == NULL)
        return GSS_S_BAD_NAME;

    if (mech->gss_get_name_attribute == NULL)
        return GSS_S_UNAVAILABLE;

    status = (*mech->gss_get_name_attribute)(minor_status,
                                             union_name->mech_name,
                                             attr,
                                             authenticated,
                                             complete,
                                             value,
                                             display_value,
                                             more);
    if (status != GSS_S_COMPLETE)
        map_error(minor_status, mech);

    return status;
}
