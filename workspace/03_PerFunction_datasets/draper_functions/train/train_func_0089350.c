H5Eprint1(FILE *stream)
{
    H5E_t   *estack;
    herr_t ret_value = SUCCEED;


    FUNC_ENTER_API_NOCLEAR(FAIL)


    if(NULL == (estack = H5E_get_my_stack()))
        HGOTO_ERROR(H5E_ERROR, H5E_CANTGET, FAIL, "can't get current error stack")


    if(H5E_print(estack, stream, TRUE) < 0)
        HGOTO_ERROR(H5E_ERROR, H5E_CANTLIST, FAIL, "can't display error stack")

done:
    FUNC_LEAVE_API(ret_value)
}
