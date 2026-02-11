H5I_inc_type_ref(H5I_type_t type)
{
    H5I_id_type_t	*type_ptr;
    int ret_value;

    FUNC_ENTER_NOAPI(FAIL)


    HDassert(type > 0 && type < H5I_next_type);


    type_ptr = H5I_id_type_list_g[type];
    if(!type_ptr)
	HGOTO_ERROR(H5E_ATOM, H5E_BADGROUP, FAIL, "invalid type")


    ret_value = (int)(++(type_ptr->count));

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
