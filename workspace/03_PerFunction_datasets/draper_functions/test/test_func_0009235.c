generic_gss_display_mech_attr(
    OM_uint32         *minor_status,
    gss_const_OID      mech_attr,
    gss_buffer_t       name,
    gss_buffer_t       short_desc,
    gss_buffer_t       long_desc)
{
    size_t i;

    if (name != GSS_C_NO_BUFFER) {
        name->length = 0;
        name->value = NULL;
    }
    if (short_desc != GSS_C_NO_BUFFER) {
        short_desc->length = 0;
        short_desc->value = NULL;
    }
    if (long_desc != GSS_C_NO_BUFFER) {
        long_desc->length = 0;
        long_desc->value = NULL;
    }
    for (i = 0; i < sizeof(mech_attr_info)/sizeof(mech_attr_info[0]); i++) {
        struct mech_attr_info_desc *mai = &mech_attr_info[i];

        if (g_OID_equal(mech_attr, mai->mech_attr)) {
            if (name != GSS_C_NO_BUFFER &&
                !g_make_string_buffer((char *)mai->name.value, name)) {
                *minor_status = ENOMEM;
                return GSS_S_FAILURE;
            }
            if (short_desc != GSS_C_NO_BUFFER &&
                !g_make_string_buffer((char *)mai->short_desc.value,
                                      short_desc)) {
                *minor_status = ENOMEM;
                return GSS_S_FAILURE;
            }
            if (long_desc != GSS_C_NO_BUFFER &&
                !g_make_string_buffer((char *)mai->long_desc.value,
                                      long_desc)) {
                *minor_status = ENOMEM;
                return GSS_S_FAILURE;
            }
            return GSS_S_COMPLETE;
        }
    }

    return GSS_S_BAD_MECH_ATTR;
}
