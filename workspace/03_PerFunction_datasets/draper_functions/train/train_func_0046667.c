HCPinquire(accrec_t * access_rec, int32 *pfile_id, uint16 *ptag,
 uint16 *pref, int32 *plength, int32 *poffset, int32 *pposn, int16 *paccess,
           int16 *pspecial)
{
    CONSTR(FUNC, "HCPinquire");
    compinfo_t *info =
        (compinfo_t *) access_rec->special_info;
    uint16 data_tag,data_ref;
    int32       data_off;


    if(HTPinquire(access_rec->ddid,&data_tag,&data_ref,&data_off,NULL)==FAIL)
        HRETURN_ERROR(DFE_INTERNAL, FAIL);


    if (pfile_id != NULL)
        *pfile_id = access_rec->file_id;
    if (ptag != NULL)
        *ptag = data_tag;
    if (pref != NULL)
        *pref = data_ref;
    if (plength != NULL)
        *plength = info->length;
    if (poffset != NULL)
        *poffset = data_off;
    if (pposn != NULL)
        *pposn = access_rec->posn;
    if (paccess != NULL)
        *paccess = (int16)access_rec->access;
    if (pspecial != NULL)
        *pspecial = (int16)access_rec->special;

    return (SUCCEED);
}
