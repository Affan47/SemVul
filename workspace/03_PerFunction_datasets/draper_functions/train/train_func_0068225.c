attr_localname(OM_uint32 *minor_status,
               struct _gss_mechanism_name *mn,
               gss_buffer_t localname)
{
    OM_uint32 major_status = GSS_S_UNAVAILABLE;
    OM_uint32 tmpMinor;
    gss_buffer_desc value = GSS_C_EMPTY_BUFFER;
    gss_buffer_desc display_value = GSS_C_EMPTY_BUFFER;
    int authenticated = 0, complete = 0;
    int more = -1;

    *minor_status = 0;

    localname->length = 0;
    localname->value = NULL;

    if (mn->gmn_mech->gm_get_name_attribute == NULL)
        return GSS_S_UNAVAILABLE;

    major_status = mn->gmn_mech->gm_get_name_attribute(minor_status,
                                                       mn->gmn_name,
                                                       GSS_C_ATTR_LOCAL_LOGIN_USER,
                                                       &authenticated,
                                                       &complete,
                                                       &value,
                                                       &display_value,
                                                       &more);
    if (GSS_ERROR(major_status)) {
        _gss_mg_error(mn->gmn_mech, major_status, *minor_status);
        return major_status;
    }

    if (authenticated) {
        *localname = value;
    } else {
        major_status = GSS_S_UNAVAILABLE;
        gss_release_buffer(&tmpMinor, &value);
    }

    gss_release_buffer(&tmpMinor, &display_value);

    return major_status;
}
