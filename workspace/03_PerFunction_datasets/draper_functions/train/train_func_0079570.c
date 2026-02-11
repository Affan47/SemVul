H5T_get_offset(const H5T_t *dt)
{
    int	ret_value;

    FUNC_ENTER_NOAPI(-1)


    while(dt->shared->parent)
        dt = dt->shared->parent;
    if(!H5T_IS_ATOMIC(dt->shared))
	HGOTO_ERROR(H5E_DATATYPE, H5E_UNSUPPORTED, FAIL, "operation not defined for specified data type")


    ret_value = (int)dt->shared->u.atomic.offset;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
