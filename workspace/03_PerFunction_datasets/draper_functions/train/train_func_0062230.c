H5FO_top_decr(const H5F_t *f, haddr_t addr)
{
    H5FO_obj_count_t *obj_count;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)


    HDassert(f);
    HDassert(f->obj_count);
    HDassert(H5F_addr_defined(addr));


    if(NULL != (obj_count = (H5FO_obj_count_t *)H5SL_search(f->obj_count, &addr))) {

        (obj_count->count)--;

        if(obj_count->count == 0) {

            if(NULL == (obj_count = (H5FO_obj_count_t *)H5SL_remove(f->obj_count, &addr)))
                HGOTO_ERROR(H5E_CACHE, H5E_CANTRELEASE, FAIL, "can't remove object from container")


            obj_count = H5FL_FREE(H5FO_obj_count_t, obj_count);
        }
    }
    else
        HGOTO_ERROR(H5E_CACHE, H5E_NOTFOUND, FAIL, "can't decrement ref. count")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
