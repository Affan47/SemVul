H5I__find_id(hid_t id)
{
    H5I_type_t		type;
    H5I_id_type_t	*type_ptr;
    H5I_id_info_t	*ret_value;

    FUNC_ENTER_STATIC_NOERR


    type = H5I_TYPE(id);
    if(type <= H5I_BADID || type >= H5I_next_type)
	HGOTO_DONE(NULL)

    type_ptr = H5I_id_type_list_g[type];
    if(!type_ptr || type_ptr->init_count <= 0)
	HGOTO_DONE(NULL)


    ret_value = (H5I_id_info_t *)H5SL_search(type_ptr->ids, &id);

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
