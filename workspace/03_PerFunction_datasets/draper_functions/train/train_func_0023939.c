H5PL_load(H5PL_type_t type, int id)
{
    htri_t      found;
    const void  *plugin_info = NULL;
    const void  *ret_value = NULL;

    FUNC_ENTER_NOAPI(NULL)


    if(FALSE == H5PL_path_found_g)
        if(H5PL__init_path_table() < 0)
            HGOTO_ERROR(H5E_PLUGIN, H5E_CANTINIT, NULL, "can't initialize search path table")


    if((found = H5PL__search_table(type, id, &plugin_info)) < 0)
        HGOTO_ERROR(H5E_PLUGIN, H5E_CANTGET, NULL, "search in table failed")


    if(!found) {
        size_t	   i;

        for(i = 0; i < H5PL_num_paths_g; i++) {
            if((found = H5PL__find(type, id, H5PL_path_table_g[i], &plugin_info)) < 0)
                HGOTO_ERROR(H5E_PLUGIN, H5E_CANTGET, NULL, "search in paths failed")


            if(found) {
                HDassert(plugin_info);
                break;
            }
        }
    }


    if(found)
        ret_value = plugin_info;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
