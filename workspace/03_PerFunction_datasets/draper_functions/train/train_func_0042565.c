_gss_spnego_inquire_mechs_for_name (
            OM_uint32 * minor_status,
            gss_const_name_t input_name,
            gss_OID_set * mech_types
           )
{
    OM_uint32 ret, junk;

    ret = gss_create_empty_oid_set(minor_status, mech_types);
    if (ret)
	return ret;

    ret = gss_add_oid_set_member(minor_status,
				 GSS_SPNEGO_MECHANISM,
				 mech_types);
    if (ret)
	gss_release_oid_set(&junk, mech_types);

    return ret;
}
