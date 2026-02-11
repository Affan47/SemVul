opal_dss_pack_buffer(opal_buffer_t *buffer, const void *src, int32_t num_vals,
                  opal_data_type_t type)
{
    int rc;
    opal_dss_type_info_t *info;

    OPAL_OUTPUT( ( opal_dss_verbose, "opal_dss_pack_buffer( %p, %p, %lu, %d )\n",
                   (void*)buffer, src, (long unsigned int)num_vals, (int)type ) );


    if (OPAL_DSS_BUFFER_FULLY_DESC == buffer->type) {
        if (OPAL_SUCCESS != (rc = opal_dss_store_data_type(buffer, type))) {
            return rc;
        }
    }


    if (NULL == (info = (opal_dss_type_info_t*)opal_pointer_array_get_item(&opal_dss_types, type))) {
        return OPAL_ERR_PACK_FAILURE;
    }

    return info->odti_pack_fn(buffer, src, num_vals, type);
}
