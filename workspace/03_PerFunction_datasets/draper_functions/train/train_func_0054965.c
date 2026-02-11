HCPseek(accrec_t * access_rec, int32 offset, intn origin)
{
    CONSTR(FUNC, "HCPseek");
    compinfo_t *info;
    int32       ret_value;


    if (origin == DF_CURRENT)
        offset += access_rec->posn;
    if (origin == DF_END)
        offset += ((compinfo_t *) (access_rec->special_info))->length;
    if (offset < 0)
        HGOTO_ERROR(DFE_RANGE, FAIL);

    info = (compinfo_t *) access_rec->special_info;
    if ((ret_value = (*(info->minfo.model_funcs.seek)) (access_rec, offset, origin)) == FAIL)
        HGOTO_ERROR(DFE_MODEL, FAIL);


    access_rec->posn = offset;

done:
    if(ret_value == FAIL)
      {

      }


    return ret_value;
}
