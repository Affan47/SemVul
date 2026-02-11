H5G_get_name_by_addr(hid_t file, hid_t lapl_id, hid_t dxpl_id, const H5O_loc_t *loc,
    char *name, size_t size)
{
    H5G_gnba_iter_t udata;
    H5G_loc_t root_loc;
    hbool_t found_obj = FALSE;
    herr_t status;
    ssize_t ret_value;


    HDmemset(&udata, 0, sizeof(udata));

    FUNC_ENTER_NOAPI(FAIL)


    if(H5G_loc(file, &root_loc) < 0)
	HGOTO_ERROR(H5E_SYM, H5E_CANTGET, FAIL, "can't get root group's location")


    if(root_loc.oloc->addr == loc->addr && root_loc.oloc->file == loc->file) {
        if(NULL == (udata.path = H5MM_strdup("")))
            HGOTO_ERROR(H5E_SYM, H5E_CANTALLOC, FAIL, "can't duplicate path string")
        found_obj = TRUE;
    }
    else {

        udata.loc = loc;
        udata.lapl_id = lapl_id;
        udata.dxpl_id = dxpl_id;
        udata.path = NULL;


        if((status = H5G_visit(file, "/", H5_INDEX_NAME, H5_ITER_NATIVE, H5G_get_name_by_addr_cb, &udata, lapl_id, dxpl_id)) < 0)
            HGOTO_ERROR(H5E_SYM, H5E_BADITER, FAIL, "group traversal failed while looking for object name")
        else if(status > 0)
            found_obj = TRUE;
    }


    if(found_obj) {

        ret_value = (ssize_t)(HDstrlen(udata.path) + 1);


        if(name) {

            HDstrncpy(name, "/", 2);


            HDstrncat(name, udata.path, (size - 2));
            if((size_t)ret_value >= size)
                name[size - 1] = '\0';
        }
    }
    else
        ret_value = 0;

done:

    H5MM_xfree(udata.path);

    FUNC_LEAVE_NOAPI(ret_value)
}
