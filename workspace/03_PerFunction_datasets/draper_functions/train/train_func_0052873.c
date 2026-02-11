H5P_get_filter_by_id(H5P_genplist_t *plist, H5Z_filter_t id, unsigned int *flags,
    size_t *cd_nelmts, unsigned cd_values[],
    size_t namelen, char name[], unsigned *filter_config)
{
    H5O_pline_t         pline;
    H5Z_filter_info_t *filter;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)


    if(H5P_get(plist, H5O_CRT_PIPELINE_NAME, &pline) < 0)
        HGOTO_ERROR(H5E_PLIST, H5E_CANTGET, FAIL, "can't get pipeline")


    if(NULL == (filter = H5Z_filter_info(&pline, id)))
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "filter ID is invalid")


    if(H5P_get_filter(filter, flags, cd_nelmts, cd_values, namelen, name, filter_config) < 0)
        HGOTO_ERROR(H5E_PLIST, H5E_CANTGET, FAIL, "can't get filter info")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
