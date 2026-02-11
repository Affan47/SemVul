H5I_remove(hid_t id)
{
    H5I_id_type_t	*type_ptr;
    H5I_id_info_t	*curr_id;
    H5I_id_info_t	*last_id;
    H5I_id_info_t   *tmp_id_ptr;
    H5I_type_t		type;
    unsigned		hash_loc;
    void *	      ret_value = NULL;

    FUNC_ENTER_NOAPI(NULL)


    type = H5I_TYPE(id);
    if(type <= H5I_BADID || type >= H5I_next_type)
	HGOTO_ERROR(H5E_ARGS, H5E_BADRANGE, NULL, "invalid type number")
    type_ptr = H5I_id_type_list_g[type];
    if(type_ptr == NULL || type_ptr->count <= 0)
	HGOTO_ERROR(H5E_ATOM, H5E_BADGROUP, NULL, "invalid type")


    hash_loc = (unsigned)H5I_LOC(id, type_ptr->cls->hash_size);
    curr_id = type_ptr->id_list[hash_loc];
    if(NULL == curr_id)
	HGOTO_ERROR(H5E_ATOM, H5E_BADATOM, NULL, "invalid ID")

    last_id = NULL;
    while(curr_id != NULL) {
        if(curr_id->id == id)
            break;
        last_id = curr_id;
        curr_id = curr_id->next;
    }

    if(curr_id != NULL) {
        if(last_id == NULL) {

            type_ptr->id_list[hash_loc] = curr_id->next;
        } else {
            last_id->next = curr_id->next;
        }

        ret_value = (void *)curr_id->obj_ptr;


        if((type_ptr->reuse_ids)&&(type_ptr->free_count < MAX_FREE_ID_STRUCTS)) {
            curr_id->next = type_ptr->next_id_ptr;
            type_ptr->next_id_ptr = curr_id;
            type_ptr->free_count++;
        }

        else
            curr_id = H5FL_FREE(H5I_id_info_t, curr_id);
    }
    else {

	HGOTO_ERROR(H5E_ATOM, H5E_BADATOM, NULL, "invalid ID")
    }


    (type_ptr->ids)--;


    if(type_ptr->ids == 0) {
        while(type_ptr->next_id_ptr) {
            tmp_id_ptr = type_ptr->next_id_ptr->next;
            (void)H5FL_FREE(H5I_id_info_t, type_ptr->next_id_ptr);
            type_ptr->next_id_ptr = tmp_id_ptr;
        }
        type_ptr->free_count = 0;

        type_ptr->nextid = type_ptr->cls->reserved;
        type_ptr->wrapped = FALSE;
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
