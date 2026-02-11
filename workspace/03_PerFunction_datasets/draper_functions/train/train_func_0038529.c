H5P_get_size_pclass(H5P_genclass_t *pclass, const char *name, size_t *size)
{
    H5P_genprop_t *prop;
    herr_t ret_value=SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT

    HDassert(pclass);
    HDassert(name);
    HDassert(size);


    if((prop=H5P_find_prop_pclass(pclass,name)) == NULL)
        HGOTO_ERROR(H5E_PLIST, H5E_NOTFOUND, FAIL, "property doesn't exist")


    *size=prop->size;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
