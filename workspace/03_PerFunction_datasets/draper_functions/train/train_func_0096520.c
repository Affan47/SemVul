H5P__dxfr_xform_cmp(const void *_xform1, const void *_xform2, size_t UNUSED size)
{
    const H5Z_data_xform_t * const *xform1 = (const H5Z_data_xform_t * const *)_xform1;
    const H5Z_data_xform_t * const *xform2 = (const H5Z_data_xform_t * const *)_xform2;
    const char *pexp1, *pexp2;
    herr_t ret_value = 0;

    FUNC_ENTER_STATIC_NOERR


    HDassert(xform1);
    HDassert(xform2);
    HDassert(size == sizeof(H5Z_data_xform_t *));


    if(*xform1 == NULL && *xform2 != NULL) HGOTO_DONE(-1);
    if(*xform1 != NULL && *xform2 == NULL) HGOTO_DONE(1);

    if(*xform1) {
        HDassert(*xform2);


        pexp1 = H5Z_xform_extract_xform_str(*xform1);
        pexp2 = H5Z_xform_extract_xform_str(*xform2);


        if(pexp1 == NULL && pexp2 != NULL) HGOTO_DONE(-1);
        if(pexp1 != NULL && pexp2 == NULL) HGOTO_DONE(1);

        if(pexp1) {
            HDassert(pexp2);
            ret_value = HDstrcmp(pexp1, pexp2);
        }
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
