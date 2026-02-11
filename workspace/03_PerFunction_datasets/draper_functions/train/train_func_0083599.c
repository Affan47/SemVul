H5I__clear_type_cb(void *_id, void H5_ATTR_UNUSED *key, void *_udata)
{
    H5I_id_info_t       *id = (H5I_id_info_t *)_id;
    H5I_clear_type_ud_t *udata = (H5I_clear_type_ud_t *)_udata;
    htri_t              ret_value = FALSE;

    FUNC_ENTER_STATIC_NOERR

    HDassert(id);
    HDassert(udata);
    HDassert(udata->type_ptr);


    if(udata->force || (id->count - (!udata->app_ref * id->app_count)) <= 1) {


        if(udata->type_ptr->cls->free_func && (udata->type_ptr->cls->free_func)((void *)id->obj_ptr) < 0) {
            if(udata->force) {
#ifdef H5I_DEBUG
                if(H5DEBUG(I)) {
                    fprintf(H5DEBUG(I), "H5I: free type=%d obj=0x%08lx "
                            "failure ignored\n",
                            (int)udata->type_ptr->cls->type_id,
                            (unsigned long)(id->obj_ptr));
                }
#endif


                ret_value = TRUE;
            }
        }
        else {

            ret_value = TRUE;
        }


        if(ret_value) {

            id = H5FL_FREE(H5I_id_info_t, id);


            udata->type_ptr->id_count--;
        }
    }

    FUNC_LEAVE_NOAPI(ret_value)
}
