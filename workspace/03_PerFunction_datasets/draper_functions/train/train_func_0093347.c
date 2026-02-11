H5Pset_nbit(hid_t plist_id)
{
    H5O_pline_t         pline;
    H5P_genplist_t *plist;
    herr_t ret_value=SUCCEED;

    FUNC_ENTER_API(H5Pset_nbit, FAIL)
    H5TRACE1("e", "i", plist_id);


    if(TRUE != H5P_isa_class(plist_id, H5P_DATASET_CREATE))
        HGOTO_ERROR (H5E_ARGS, H5E_BADTYPE, FAIL, "not a dataset creation property list")


    if(NULL == (plist = (H5P_genplist_t *)H5I_object(plist_id)))
        HGOTO_ERROR(H5E_ATOM, H5E_BADATOM, FAIL, "can't find object for ID")


    if(H5P_get(plist, H5O_CRT_PIPELINE_NAME, &pline) < 0)
        HGOTO_ERROR(H5E_PLIST, H5E_CANTGET, FAIL, "can't get pipeline")
    if(H5Z_append(&pline, H5Z_FILTER_NBIT, H5Z_FLAG_OPTIONAL, (size_t)0, NULL) < 0)
        HGOTO_ERROR(H5E_PLINE, H5E_CANTINIT, FAIL, "unable to add nbit filter to pipeline")
    if(H5P_set(plist, H5O_CRT_PIPELINE_NAME, &pline) < 0)
        HGOTO_ERROR(H5E_PLINE, H5E_CANTINIT, FAIL, "unable to set pipeline")

done:
    FUNC_LEAVE_API(ret_value)
}
