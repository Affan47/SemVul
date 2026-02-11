H5Tget_norm(hid_t type_id)
{
    H5T_t	*dt;
    H5T_norm_t	ret_value;

    FUNC_ENTER_API(H5T_NORM_ERROR)
    H5TRACE1("Tn", "i", type_id);


    if(NULL == (dt = (H5T_t *)H5I_object_verify(type_id, H5I_DATATYPE)))
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, H5T_NORM_ERROR, "not a datatype")
    while(dt->shared->parent)
        dt = dt->shared->parent;
    if(H5T_FLOAT != dt->shared->type)
	HGOTO_ERROR(H5E_DATATYPE, H5E_BADTYPE, H5T_NORM_ERROR, "operation not defined for datatype class")


    ret_value = dt->shared->u.atomic.u.f.norm;

done:
    FUNC_LEAVE_API(ret_value)
}
