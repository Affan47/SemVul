opal_dss_pack_string(opal_buffer_t *buffer, const void *src,
                         int32_t num_vals, opal_data_type_t type)
{
    int ret = OPAL_SUCCESS;
    int32_t i, len;
    char **ssrc = (char**) src;

    for (i = 0; i < num_vals; ++i) {
        if (NULL == ssrc[i]) {
            len = 0;
            if (OPAL_SUCCESS != (ret = opal_dss_pack_int32(buffer, &len, 1, OPAL_INT32))) {
                return ret;
            }
        } else {
            len = (int32_t)strlen(ssrc[i]) + 1;
            if (OPAL_SUCCESS != (ret = opal_dss_pack_int32(buffer, &len, 1, OPAL_INT32))) {
                return ret;
            }
            if (OPAL_SUCCESS != (ret =
                opal_dss_pack_byte(buffer, ssrc[i], len, OPAL_BYTE))) {
                return ret;
            }
        }
    }

    return OPAL_SUCCESS;
}
