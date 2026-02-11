H5Tequal(hid_t type1_id, hid_t type2_id)
{
    const H5T_t	*dt1;
    const H5T_t	*dt2;
    htri_t		ret_value;

    FUNC_ENTER_API(FAIL)
    H5TRACE2("t", "ii", type1_id, type2_id);


    if(NULL == (dt1 = (H5T_t *)H5I_object_verify(type1_id, H5I_DATATYPE)))
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a datatype")
    if(NULL == (dt2 = (H5T_t *)H5I_object_verify(type2_id, H5I_DATATYPE)))
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a datatype")

    ret_value = (0 == H5T_cmp(dt1, dt2, FALSE)) ? TRUE : FALSE;

done:
    FUNC_LEAVE_API(ret_value)
}
