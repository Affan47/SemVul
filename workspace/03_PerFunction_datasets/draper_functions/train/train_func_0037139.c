H5FS_hdr_dest(H5FS_t *fspace)
{
    unsigned u;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(fspace);


    for(u = 0; u < fspace->nclasses ; u++) {

        if(fspace->sect_cls[u].term_cls)
            if((fspace->sect_cls[u].term_cls)(&fspace->sect_cls[u]) < 0)
                HGOTO_ERROR(H5E_RESOURCE, H5E_CANTRELEASE, FAIL, "unable to finalize section class")
    }


    if(fspace->sect_cls)
        fspace->sect_cls = (H5FS_section_class_t *)H5FL_SEQ_FREE(H5FS_section_class_t, fspace->sect_cls);


    fspace = H5FL_FREE(H5FS_t, fspace);

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
