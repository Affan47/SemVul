HCPcdeflate_endaccess(accrec_t * access_rec)
{
    CONSTR(FUNC, "HCPcdeflate_endaccess");
    compinfo_t *info;
    comp_coder_deflate_info_t *deflate_info;

    info = (compinfo_t *) access_rec->special_info;
    deflate_info = &(info->cinfo.coder_info.deflate_info);


    if (HCIcdeflate_term(info,deflate_info->acc_mode) == FAIL)
        HRETURN_ERROR(DFE_CTERM, FAIL);


    HDfree(deflate_info->io_buf);


    if (Hendaccess(info->aid) == FAIL)
        HRETURN_ERROR(DFE_CANTCLOSE, FAIL);

    return (SUCCEED);
}
