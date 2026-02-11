H5P_dcrt_reg_prop(H5P_genclass_t *pclass)
{
    H5O_layout_t layout = H5D_CRT_LAYOUT_DEF;
    H5O_fill_t fill = H5D_CRT_FILL_VALUE_DEF;
    unsigned alloc_time_state = H5D_CRT_ALLOC_TIME_STATE_DEF;
    H5O_efl_t efl = H5D_CRT_EXT_FILE_LIST_DEF;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT(H5P_dcrt_reg_prop)


    if(H5P_register_real(pclass, H5D_CRT_LAYOUT_NAME, H5D_CRT_LAYOUT_SIZE, &layout, NULL, NULL, NULL, NULL, NULL, H5D_CRT_LAYOUT_CMP, NULL) < 0)
       HGOTO_ERROR(H5E_PLIST, H5E_CANTINSERT, FAIL, "can't insert property into class")


    if(H5P_register_real(pclass, H5D_CRT_FILL_VALUE_NAME, H5D_CRT_FILL_VALUE_SIZE, &fill, NULL, NULL, NULL, NULL, NULL, H5D_CRT_FILL_VALUE_CMP, NULL) < 0)
       HGOTO_ERROR(H5E_PLIST, H5E_CANTINSERT, FAIL, "can't insert property into class")


    if(H5P_register_real(pclass, H5D_CRT_ALLOC_TIME_STATE_NAME, H5D_CRT_ALLOC_TIME_STATE_SIZE, &alloc_time_state, NULL, NULL, NULL, NULL, NULL, NULL, NULL) < 0)
        HGOTO_ERROR(H5E_PLIST, H5E_CANTINSERT, FAIL, "can't insert property into class")


    if(H5P_register_real(pclass, H5D_CRT_EXT_FILE_LIST_NAME, H5D_CRT_EXT_FILE_LIST_SIZE, &efl, NULL, NULL, NULL, NULL, NULL, H5D_CRT_EXT_FILE_LIST_CMP, NULL) < 0)
       HGOTO_ERROR(H5E_PLIST, H5E_CANTINSERT, FAIL, "can't insert property into class")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
