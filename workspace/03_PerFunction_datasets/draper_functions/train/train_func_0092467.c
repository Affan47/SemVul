H5P_unregister(H5P_genclass_t *pclass, const char *name)
{
    H5P_genprop_t *prop;
    herr_t      ret_value=SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT

    HDassert(pclass);
    HDassert(name);


    if((prop = (H5P_genprop_t *)H5SL_search(pclass->props,name)) == NULL)
        HGOTO_ERROR(H5E_PLIST,H5E_NOTFOUND,FAIL,"can't find property in skip list")


    if(H5SL_remove(pclass->props,prop->name) == NULL)
        HGOTO_ERROR(H5E_PLIST,H5E_CANTDELETE,FAIL,"can't remove property from skip list")


    H5P_free_prop(prop);


    pclass->nprops--;


    pclass->revision = H5P_GET_NEXT_REV;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
