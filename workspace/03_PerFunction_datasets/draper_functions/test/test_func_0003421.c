opal_dss_pack(opal_buffer_t *buffer, const void *src, int32_t num_vals,
                  opal_data_type_t type)
{
    int rc;


    if (NULL == buffer) {
        return OPAL_ERR_BAD_PARAM;
    }


    if (OPAL_DSS_BUFFER_FULLY_DESC == buffer->type) {
        if (OPAL_SUCCESS != (rc = opal_dss_store_data_type(buffer, OPAL_INT32))) {
            return rc;
        }
    }
    if (OPAL_SUCCESS != (rc = opal_dss_pack_int32(buffer, &num_vals, 1, OPAL_INT32))) {
        return rc;
    }


    return opal_dss_pack_buffer(buffer, src, num_vals, type);
}
