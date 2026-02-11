mech_authorize_localname(OM_uint32 *minor_status,
	                 const struct _gss_name *name,
	                 const struct _gss_name *user)
{
    OM_uint32 major_status = GSS_S_NAME_NOT_MN;
    struct _gss_mechanism_name *mn;

    HEIM_SLIST_FOREACH(mn, &name->gn_mn, gmn_link) {
        gssapi_mech_interface m = mn->gmn_mech;

        if (m->gm_authorize_localname == NULL) {
            major_status = GSS_S_UNAVAILABLE;
            continue;
        }

        major_status = m->gm_authorize_localname(minor_status,
                                                 mn->gmn_name,
                                                 &user->gn_value,
                                                 &user->gn_type);
        if (major_status != GSS_S_UNAUTHORIZED)
            break;
    }

    return major_status;
}
