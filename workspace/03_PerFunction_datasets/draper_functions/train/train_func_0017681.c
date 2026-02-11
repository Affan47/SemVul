krb5int_gss_use_kdc_context(OM_uint32 *minor_status,
                            const gss_OID desired_mech,
                            const gss_OID desired_object,
                            gss_buffer_t value)
{
    OM_uint32 err;

    *minor_status = 0;

    err = gss_krb5int_initialize_library();
    if (err)
        return err;
    k5_mutex_lock(&kg_kdc_flag_mutex);
    kdc_flag = 1;
    k5_mutex_unlock(&kg_kdc_flag_mutex);
    return GSS_S_COMPLETE;
}
