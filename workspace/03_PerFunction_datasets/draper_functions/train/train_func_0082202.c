gx_serialize_ICC(const gs_color_space * pcs, stream * s)
{
    gsicc_serialized_profile_t *profile__serial;
    uint n;
    int code = gx_serialize_cspace_type(pcs, s);

    if (code < 0)
        return code;
    profile__serial = (gsicc_serialized_profile_t*) pcs->cmm_icc_profile_data;
    code = sputs(s, (byte *)profile__serial, GSICC_SERIALIZED_SIZE, &n);
    return(code);
}
