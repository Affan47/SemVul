H5Tenum_valueof(hid_t type, const char *name, void *value)
{
    H5T_t	*dt;
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_API(FAIL)
    H5TRACE3("e", "i*sx", type, name, value);


    if(NULL == (dt = (H5T_t *)H5I_object_verify(type, H5I_DATATYPE)))
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a data type")
    if(H5T_ENUM != dt->shared->type)
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not an enumeration data type")
    if(!name || !*name)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "no name")
    if(!value)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "no value buffer")

    if(H5T_enum_valueof(dt, name, value) < 0)
	HGOTO_ERROR(H5E_DATATYPE, H5E_CANTINIT, FAIL, "valueof query failed")

done:
    FUNC_LEAVE_API(ret_value)
}
