HCIcrle_init(accrec_t * access_rec)
{
    CONSTR(FUNC, "HCIcrle_init");
    compinfo_t *info;
    comp_coder_rle_info_t *rle_info;

    info = (compinfo_t *) access_rec->special_info;
    if (Hseek(info->aid, 0, DF_START) == FAIL)
        HRETURN_ERROR(DFE_SEEKERROR, FAIL);

    rle_info = &(info->cinfo.coder_info.rle_info);


    rle_info->rle_state = RLE_INIT;
    rle_info->buf_pos = 0;
    rle_info->last_byte = (uintn) RLE_NIL;
    rle_info->second_byte = (uintn) RLE_NIL;
    rle_info->offset = 0;

    return (SUCCEED);
}
