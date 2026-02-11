H5Aiterate1(hid_t loc_id, unsigned *attr_num, H5A_operator1_t op, void *op_data)
{
    H5A_attr_iter_op_t  attr_op;
    hsize_t		start_idx;
    hsize_t		last_attr;
    herr_t	        ret_value;

    FUNC_ENTER_API(FAIL)
    H5TRACE4("e", "i*Iux*x", loc_id, attr_num, op, op_data);


    if(H5I_ATTR == H5I_get_type(loc_id))
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "location is not valid for an attribute")


    attr_op.op_type = H5A_ATTR_OP_APP;
    attr_op.u.app_op = op;


    last_attr = start_idx = (hsize_t)(attr_num ? *attr_num : 0);
    if((ret_value = H5O_attr_iterate(loc_id, H5AC_ind_dxpl_id, H5_INDEX_CRT_ORDER, H5_ITER_INC, start_idx, &last_attr, &attr_op, op_data)) < 0)
        HERROR(H5E_ATTR, H5E_BADITER, "error iterating over attributes");


    if(attr_num)
        *attr_num = (unsigned)last_attr;

done:
    FUNC_LEAVE_API(ret_value)
}
