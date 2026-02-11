H5S_hyper_copy (H5S_t *dst, const H5S_t *src, hbool_t share_selection)
{
    H5S_hyper_sel_t *dst_hslab;
    const H5S_hyper_sel_t *src_hslab;
    herr_t ret_value=SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)

    HDassert(src);
    HDassert(dst);


    if(NULL == (dst->select.sel_info.hslab = H5FL_MALLOC(H5S_hyper_sel_t)))
        HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, FAIL, "can't allocate hyperslab info")


    dst_hslab=dst->select.sel_info.hslab;
    src_hslab=src->select.sel_info.hslab;


    dst_hslab->diminfo_valid=src_hslab->diminfo_valid;
    if(src_hslab->diminfo_valid) {
        size_t u;

        for(u=0; u<src->extent.rank; u++) {
            dst_hslab->opt_diminfo[u]=src_hslab->opt_diminfo[u];
            dst_hslab->app_diminfo[u]=src_hslab->app_diminfo[u];
        }
    }
    dst->select.sel_info.hslab->span_lst=src->select.sel_info.hslab->span_lst;


    if(src->select.sel_info.hslab->span_lst!=NULL) {
        if(share_selection) {

            dst->select.sel_info.hslab->span_lst->count++;
        }
        else

            dst->select.sel_info.hslab->span_lst = H5S_hyper_copy_span(src->select.sel_info.hslab->span_lst);
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
