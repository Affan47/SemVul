H5P_lcrt_reg_prop(H5P_genclass_t *pclass)
{
    unsigned intmd_group = H5L_CRT_INTERMEDIATE_GROUP_DEF;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)


    if(H5P_register_real(pclass, H5L_CRT_INTERMEDIATE_GROUP_NAME, H5L_CRT_INTERMEDIATE_GROUP_SIZE, &intmd_group, NULL, NULL, NULL, NULL, NULL, NULL, NULL) < 0)
        HGOTO_ERROR(H5E_PLIST, H5E_CANTINSERT, FAIL, "can't insert property into class")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
