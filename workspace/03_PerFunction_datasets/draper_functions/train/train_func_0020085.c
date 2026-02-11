HMCPendaccess(accrec_t * access_rec )
{
    CONSTR(FUNC, "HMCPendaccess");
    filerec_t   *file_rec = NULL;
    intn        ret_value = SUCCEED;


    if (access_rec == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);


    file_rec = HAatom_object(access_rec->file_id);


    if (BADFREC(file_rec))
        HGOTO_ERROR(DFE_INTERNAL, FAIL);


    if (HMCPcloseAID(access_rec) == FAIL)
        HGOTO_ERROR(DFE_INTERNAL, FAIL);


    if (HTPendaccess(access_rec->ddid) == FAIL)
        HGOTO_ERROR(DFE_CANTENDACCESS, FAIL);


    file_rec->attach--;

#ifdef CHK_DEBUG_2
    fprintf(stderr,"HMCPendaccess: file_rec->attach =%d \n", file_rec->attach);

#endif

    HIrelease_accrec_node(access_rec);

  done:
    if(ret_value == FAIL)
      {

      }


    return ret_value;
}
