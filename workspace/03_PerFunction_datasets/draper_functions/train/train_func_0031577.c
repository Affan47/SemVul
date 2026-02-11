opal_dss_pack_float(opal_buffer_t *buffer, const void *src,
                        int32_t num_vals, opal_data_type_t type)
{
    int64_t tmp[2];
    int ret = OPAL_SUCCESS;
    int32_t i;
    float *ssrc = (float*)src;

    for (i = 0; i < num_vals; ++i) {
        tmp[0] = (int64_t)ssrc[i];
        tmp[1] = (int64_t)(1000000.0 * (ssrc[i] - tmp[0]));
        if (OPAL_SUCCESS != (ret = opal_dss_pack_int64(buffer, tmp, 2, OPAL_INT64))) {
            return ret;
        }
    }

    return OPAL_SUCCESS;
}
