H5G_open(const H5G_loc_t *loc, hid_t dxpl_id)
{
    H5G_t           *grp = NULL;
    H5G_shared_t    *shared_fo;
    H5G_t           *ret_value;

    FUNC_ENTER_NOAPI(NULL)


    HDassert(loc);


    if(NULL == (grp = H5FL_CALLOC(H5G_t)))
        HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, NULL, "can't allocate space for group")


    if(H5O_loc_copy(&(grp->oloc), loc->oloc, H5_COPY_SHALLOW) < 0)
        HGOTO_ERROR(H5E_SYM, H5E_CANTCOPY, NULL, "can't copy object location")
    if(H5G_name_copy(&(grp->path), loc->path, H5_COPY_SHALLOW) < 0)
        HGOTO_ERROR(H5E_SYM, H5E_CANTCOPY, NULL, "can't copy path")


    if((shared_fo = (H5G_shared_t *)H5FO_opened(grp->oloc.file, grp->oloc.addr)) == NULL) {


        H5E_clear_stack(NULL);


        if(H5G_open_oid(grp, dxpl_id) < 0)
            HGOTO_ERROR(H5E_SYM, H5E_NOTFOUND, NULL, "not found")


        if(H5FO_insert(grp->oloc.file, grp->oloc.addr, grp->shared, FALSE) < 0) {
            grp->shared = H5FL_FREE(H5G_shared_t, grp->shared);
            HGOTO_ERROR(H5E_SYM, H5E_CANTINSERT, NULL, "can't insert group into list of open objects")
        }


        if(H5FO_top_incr(grp->oloc.file, grp->oloc.addr) < 0)
            HGOTO_ERROR(H5E_SYM, H5E_CANTINC, NULL, "can't increment object count")


        grp->shared->fo_count = 1;
    }
    else {

        grp->shared = shared_fo;


        shared_fo->fo_count++;


        if(H5FO_top_count(grp->oloc.file, grp->oloc.addr) == 0) {

            if(H5O_open(&(grp->oloc)) < 0)
                HGOTO_ERROR(H5E_SYM, H5E_CANTOPENOBJ, NULL, "unable to open object header")
        }


        if(H5FO_top_incr(grp->oloc.file, grp->oloc.addr) < 0)
            HGOTO_ERROR(H5E_SYM, H5E_CANTINC, NULL, "can't increment object count")
    }


    ret_value = grp;

done:
    if(!ret_value && grp) {
        H5O_loc_free(&(grp->oloc));
        H5G_name_free(&(grp->path));
        grp = H5FL_FREE(H5G_t, grp);
    }

    FUNC_LEAVE_NOAPI(ret_value)
}
