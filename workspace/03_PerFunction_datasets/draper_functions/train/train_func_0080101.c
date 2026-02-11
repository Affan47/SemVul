gss_set_name_attribute(OM_uint32 *minor_status,
		       gss_name_t input_name,
		       int complete,
		       gss_buffer_t attr,
		       gss_buffer_t value)
{
    OM_uint32 major_status = GSS_S_UNAVAILABLE;
    struct _gss_name *name = (struct _gss_name *) input_name;
    struct _gss_mechanism_name *mn;

    *minor_status = 0;

    if (input_name == GSS_C_NO_NAME)
        return GSS_S_BAD_NAME;

    HEIM_SLIST_FOREACH(mn, &name->gn_mn, gmn_link) {
        gssapi_mech_interface m = mn->gmn_mech;

        if (!m->gm_set_name_attribute)
            continue;

        major_status = m->gm_set_name_attribute(minor_status,
                                                mn->gmn_name,
                                                complete,
                                                attr,
                                                value);
        if (GSS_ERROR(major_status))
            _gss_mg_error(m, major_status, *minor_status);
        else
            break;
    }

    return major_status;
}
