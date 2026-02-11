H5Aiterate2(hid_t loc_id, H5_index_t idx_type, H5_iter_order_t order,
    hsize_t *idx, H5A_operator2_t op, void *op_data)
{
    H5A_attr_iter_op_t attr_op;
    hsize_t	start_idx;
    hsize_t	last_attr;
    herr_t	ret_value;

    FUNC_ENTER_API(FAIL)
    H5TRACE6("e", "iIiIo*hx*x", loc_id, idx_type, order, idx, op, op_data);


    if(H5I_ATTR == H5I_get_type(loc_id))
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "location is not valid for an attribute")
    if(idx_type <= H5_INDEX_UNKNOWN || idx_type >= H5_INDEX_N)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "invalid index type specified")
    if(order <= H5_ITER_UNKNOWN || order >= H5_ITER_N)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "invalid iteration order specified")


    attr_op.op_type = H5A_ATTR_OP_APP2;
    attr_op.u.app_op2 = op;


    last_attr = start_idx = (idx ? *idx : 0);
    if((ret_value = H5O_attr_iterate(loc_id, H5AC_ind_dxpl_id, idx_type, order, start_idx, &last_attr, &attr_op, op_data)) < 0)
        HERROR(H5E_ATTR, H5E_BADITER, "error iterating over attributes");


    if(idx)
        *idx = last_attr;

done:
    FUNC_LEAVE_API(ret_value)
}
