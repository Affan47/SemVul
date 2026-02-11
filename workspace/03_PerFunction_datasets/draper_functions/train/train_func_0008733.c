H5Ovisit(hid_t obj_id, H5_index_t idx_type, H5_iter_order_t order,
    H5O_iterate_t op, void *op_data)
{
    herr_t      ret_value;

    FUNC_ENTER_API(FAIL)
    H5TRACE5("e", "iIiIox*x", obj_id, idx_type, order, op, op_data);


    if(idx_type <= H5_INDEX_UNKNOWN || idx_type >= H5_INDEX_N)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "invalid index type specified")
    if(order <= H5_ITER_UNKNOWN || order >= H5_ITER_N)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "invalid iteration order specified")
    if(!op)
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "no callback operator specified")


    if((ret_value = H5O_visit(obj_id, ".", idx_type, order, op, op_data, H5P_LINK_ACCESS_DEFAULT, H5AC_ind_dxpl_id)) < 0)
	HGOTO_ERROR(H5E_SYM, H5E_BADITER, FAIL, "object visitation failed")

done:
    FUNC_LEAVE_API(ret_value)
}
