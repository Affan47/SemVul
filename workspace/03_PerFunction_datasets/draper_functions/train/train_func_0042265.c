H5S_select_none(H5S_t *space)
{
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)


    HDassert(space);


    if(H5S_SELECT_RELEASE(space) < 0)
        HGOTO_ERROR(H5E_DATASPACE, H5E_CANTDELETE, FAIL, "can't release hyperslab")


    space->select.num_elem = 0;


    space->select.type = H5S_sel_none;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
