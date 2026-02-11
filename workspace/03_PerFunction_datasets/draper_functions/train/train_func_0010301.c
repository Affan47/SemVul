H5P_copy_prop_pclass(hid_t dst_id, hid_t src_id, const char *name)
{
    H5P_genclass_t *src_pclass;
    H5P_genclass_t *dst_pclass;
    H5P_genclass_t *orig_dst_pclass;
    H5P_genprop_t *prop;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(name);


    if(NULL == (src_pclass = (H5P_genclass_t *)H5I_object(src_id)))
        HGOTO_ERROR(H5E_PLIST, H5E_NOTFOUND, FAIL, "source property class object doesn't exist")
    if(NULL == (dst_pclass = (H5P_genclass_t *)H5I_object(dst_id)))
        HGOTO_ERROR(H5E_PLIST, H5E_NOTFOUND, FAIL, "destination property class object doesn't exist")


    if(NULL == (prop = H5P_find_prop_pclass(src_pclass, name)))
        HGOTO_ERROR(H5E_PLIST, H5E_NOTFOUND, FAIL, "unable to locate property")


    if(H5P_exist_pclass(dst_pclass, name)) {

        if(H5P_unregister(dst_pclass, name) < 0)
            HGOTO_ERROR(H5E_PLIST, H5E_CANTDELETE, FAIL, "unable to remove property")
    }


    orig_dst_pclass = dst_pclass;
    if(H5P_register(&dst_pclass, name, prop->size, prop->value, prop->create, prop->set, prop->get,
            prop->del, prop->copy, prop->cmp, prop->close) < 0)
        HGOTO_ERROR(H5E_PLIST, H5E_CANTDELETE, FAIL, "unable to remove property")


    if(dst_pclass != orig_dst_pclass) {
        H5P_genclass_t *old_dst_pclass;


        if(NULL == (old_dst_pclass = (H5P_genclass_t *)H5I_subst(dst_id, dst_pclass)))
            HGOTO_ERROR(H5E_PLIST, H5E_CANTSET, FAIL, "unable to substitute property class in ID")
        HDassert(old_dst_pclass == orig_dst_pclass);


        if(H5P_close_class(old_dst_pclass) < 0)
            HGOTO_ERROR(H5E_PLIST, H5E_CANTCLOSEOBJ, FAIL, "unable to close original property class after substitution")
    }

done:


    FUNC_LEAVE_NOAPI(ret_value)
}
