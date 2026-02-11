orte_dt_pack_std_cntr(opal_buffer_t *buffer, const void *src,
                            int32_t num_vals, opal_data_type_t type)
{
    int ret;


    if (ORTE_SUCCESS != (
                         ret = opal_dss_pack_buffer(buffer, src, num_vals, ORTE_STD_CNTR_T))) {
        ORTE_ERROR_LOG(ret);
    }

    return ret;
}
