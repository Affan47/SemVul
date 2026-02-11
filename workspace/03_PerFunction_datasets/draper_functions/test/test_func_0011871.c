H5Tenum_nameof(hid_t type, const void *value, char *name, size_t size)
{
    H5T_t	*dt = NULL;
    herr_t      ret_value=SUCCEED;

    FUNC_ENTER_API(FAIL)
    H5TRACE4("e", "i*xxz", type, value, name, size);


    if(NULL == (dt = (H5T_t *)H5I_object_verify(type, H5I_DATATYPE)))
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a data type")
    if(H5T_ENUM != dt->shared->type)
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not an enumeration data type")
    if (!value)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "no value supplied")
    if (!name)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "no name buffer supplied")

    if (NULL==H5T_enum_nameof(dt, value, name, size))
	HGOTO_ERROR(H5E_DATATYPE, H5E_CANTINIT, FAIL, "nameof query failed")

done:
    FUNC_LEAVE_API(ret_value)
}
