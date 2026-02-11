H5HF_sect_init_cls(H5FS_section_class_t *cls, H5HF_hdr_t *hdr)
{
    H5HF_sect_private_t *cls_prvt;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(cls);
    HDassert(!cls->cls_private);


    if(NULL == (cls_prvt = (H5HF_sect_private_t *)H5MM_malloc(sizeof(H5HF_sect_private_t))))
	HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, FAIL, "memory allocation failed")
    cls_prvt->hdr = hdr;
    cls->cls_private = cls_prvt;


    if(H5HF_hdr_incr(hdr) < 0)
        HGOTO_ERROR(H5E_HEAP, H5E_CANTINC, FAIL, "can't increment reference count on shared heap header")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
