H5Zget_filter_info(H5Z_filter_t filter, unsigned int *filter_config_flags)
{
    H5Z_class2_t *fclass;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_API(FAIL)
    H5TRACE2("e", "Zf*Iu", filter, filter_config_flags);


    if(NULL == (fclass = H5Z_find(filter)))
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "Filter not defined")


    if(filter_config_flags != NULL) {
        *filter_config_flags = 0;

        if(fclass->encoder_present)
            *filter_config_flags |= H5Z_FILTER_CONFIG_ENCODE_ENABLED;
        if(fclass->decoder_present)
            *filter_config_flags |= H5Z_FILTER_CONFIG_DECODE_ENABLED;
    }

done:
    FUNC_LEAVE_API(ret_value)
}
