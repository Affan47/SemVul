HLPendaccess(accrec_t * access_rec)
{
    CONSTR(FUNC, "HLPendaccess");
    filerec_t  *file_rec;
    intn      ret_value = SUCCEED;


    file_rec = HAatom_object(access_rec->file_id);


    HLPcloseAID(access_rec);


    if (HTPendaccess(access_rec->ddid) == FAIL)
      HGOTO_ERROR(DFE_CANTFLUSH, FAIL);


    if (BADFREC(file_rec))
        HGOTO_ERROR(DFE_INTERNAL, FAIL);


    file_rec->attach--;


    HIrelease_accrec_node(access_rec);

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}
