HCPinfo(accrec_t * access_rec, sp_info_block_t * info_block)
{
    CONSTR(FUNC, "HCPinfo");
    compinfo_t *info =
    (compinfo_t *) access_rec->special_info;


    if (access_rec->special != SPECIAL_COMP)
        HRETURN_ERROR(DFE_INTERNAL, FAIL);


    info_block->key = SPECIAL_COMP;

    info_block->comp_type = (int32)info->cinfo.coder_type;
    info_block->model_type = (int32)info->minfo.model_type;
    info_block->comp_size = Hlength(access_rec->file_id, DFTAG_COMPRESSED, info->comp_ref);

    return SUCCEED;
}
