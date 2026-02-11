H5P_copy_pclass(H5P_genclass_t *pclass)
{
    H5P_genclass_t *new_pclass = NULL;
    H5P_genprop_t *pcopy;
    H5P_genclass_t *ret_value=NULL;

    FUNC_ENTER_NOAPI_NOINIT

    HDassert(pclass);


    if(NULL == (new_pclass = H5P_create_class(pclass->parent, pclass->name, pclass->type, pclass->create_func, pclass->create_data, pclass->copy_func, pclass->copy_data, pclass->close_func, pclass->close_data)))
        HGOTO_ERROR(H5E_PLIST, H5E_CANTCREATE, NULL, "unable to create property list class")


    if(pclass->nprops > 0) {
        H5SL_node_t *curr_node;


        curr_node=H5SL_first(pclass->props);
        while(curr_node!=NULL) {

            if(NULL == (pcopy = H5P_dup_prop((H5P_genprop_t *)H5SL_item(curr_node), H5P_PROP_WITHIN_CLASS)))
                HGOTO_ERROR(H5E_PLIST, H5E_CANTCOPY, NULL,"Can't copy property")


            if(H5P_add_prop(new_pclass->props,pcopy) < 0)
                HGOTO_ERROR(H5E_PLIST, H5E_CANTINSERT, NULL,"Can't insert property into class")


            new_pclass->nprops++;


            curr_node=H5SL_next(curr_node);
        }
    }


    ret_value=new_pclass;

done:
    if(ret_value==NULL && new_pclass)
        H5P_close_class(new_pclass);

    FUNC_LEAVE_NOAPI(ret_value)
}
