H5I_term_interface(void)
{
    H5I_id_type_t	*type_ptr;
    H5I_type_t		type;
    int		n = 0;

    FUNC_ENTER_NOAPI_NOINIT_NOERR

    if(H5_interface_initialize_g) {

        for(type = (H5I_type_t)0; type < H5I_next_type; H5_INC_ENUM(H5I_type_t, type)) {
            if((type_ptr = H5I_id_type_list_g[type]) && type_ptr->ids)
                n++;
        }


        if(0 == n) {
            for(type = (H5I_type_t)0; type < H5I_next_type; H5_INC_ENUM(H5I_type_t,type)) {
                type_ptr = H5I_id_type_list_g[type];
                if(type_ptr) {
                    HDassert(NULL == type_ptr->ids);
                    type_ptr = H5FL_FREE(H5I_id_type_t, type_ptr);
                    H5I_id_type_list_g[type] = NULL;
                }
            }
        }


        H5_interface_initialize_g = 0;
    }

    FUNC_LEAVE_NOAPI(n)
}
