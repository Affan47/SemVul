opal_dss_unpack_int(opal_buffer_t *buffer, void *dest,
                        int32_t *num_vals, opal_data_type_t type)
{
    int ret;
    opal_data_type_t remote_type;

    if (OPAL_DSS_BUFFER_FULLY_DESC == buffer->type) {

        if (OPAL_SUCCESS != (ret = opal_dss_peek_type(buffer, &remote_type))) {
            return ret;
        }
    } else {
        if (OPAL_SUCCESS != (ret = opal_dss_get_data_type(buffer, &remote_type))) {
            return ret;
        }
    }

    if (remote_type == DSS_TYPE_INT) {


        if (OPAL_SUCCESS != (ret = opal_dss_unpack_buffer(buffer, dest, num_vals, DSS_TYPE_INT))) {
        }
    } else {

        UNPACK_SIZE_MISMATCH(int, remote_type, ret);
    }

    return ret;
}
