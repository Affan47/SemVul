H5G_root_loc(H5F_t *f, H5G_loc_t *loc)
{
    H5G_t *root_grp;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)

    HDassert(f);
    HDassert(loc);


    root_grp = H5G_rootof(f);
    HDassert(root_grp);


    if(NULL == (loc->oloc = H5G_oloc(root_grp)))
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "unable to get object location for root group")
    if(NULL == (loc->path = H5G_nameof(root_grp)))
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "unable to get path for root group")


    if(!H5F_is_mount(f)) {
        loc->oloc->file = f;
        loc->oloc->holding_file = FALSE;
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
