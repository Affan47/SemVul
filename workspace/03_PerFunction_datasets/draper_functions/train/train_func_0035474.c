HCPgetcompress(int32 file_id,
              uint16 data_tag, uint16 data_ref,
              comp_coder_t* comp_type,
              comp_info* c_info)
{
    CONSTR(FUNC, "HCPgetcompress");
    int32   aid=0, status;
    accrec_t*    access_rec=NULL;
    compinfo_t*  info=NULL;
    model_info  m_info;
    int32       ret_value=SUCCEED;


    HEclear();


    aid = Hstartread(file_id, data_tag, data_ref);


    access_rec = HAatom_object(aid);
    if (access_rec == NULL) HGOTO_ERROR(DFE_ARGS, FAIL);


    if (access_rec->special == SPECIAL_COMP)
    {
        info = (compinfo_t *) access_rec->special_info;
        if (info == NULL) HGOTO_ERROR(DFE_COMPINFO, FAIL);

        status = HCIread_header(access_rec, info, c_info, &m_info);
        if (status == FAIL) HGOTO_ERROR(DFE_COMPINFO, FAIL);


        *comp_type = info->cinfo.coder_type;

    }


    else if (access_rec->special == SPECIAL_CHUNKED)
    {
	status = HMCgetcompress(access_rec, comp_type, c_info);
        if (status == FAIL) HGOTO_ERROR(DFE_COMPINFO, FAIL);
    }


    else


     {

        *comp_type = COMP_CODE_NONE;
        HGOTO_ERROR(DFE_ARGS, FAIL);
     }

    if (Hendaccess(aid)== FAIL)
        HGOTO_ERROR(DFE_CANTENDACCESS, FAIL);

done:
  if(ret_value == FAIL)
    {

        if (aid != 0)
            if (Hendaccess(aid)== FAIL)
                HERROR(DFE_CANTENDACCESS);
    }


  return ret_value;
}
