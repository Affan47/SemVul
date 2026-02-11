HCPgetdatasize(int32 file_id,
              uint16 data_tag, uint16 data_ref,
              int32* comp_size,
              int32* orig_size)
{
    CONSTR(FUNC, "HCPgetdatasize");
    uint8      *local_ptbuf=NULL, *p;
    uint16	sp_tag;
    uint16 comp_ref = 0;
    atom_t      data_id = FAIL;
    int32 len = 0;
    filerec_t  *file_rec;
    intn        ret_value=SUCCEED;


    HEclear();


    file_rec = HAatom_object(file_id);
    if (BADFREC(file_rec))
	HGOTO_ERROR(DFE_ARGS, FAIL);


    if ((data_id=HTPselect(file_rec, data_tag, data_ref))!=FAIL)
    {


	if (HTPis_special(data_id)==FALSE)
        {
	    if ((len = Hlength(file_id, data_tag, data_ref)) == FAIL)
		HGOTO_ERROR(DFE_BADLEN, FAIL);
	    *orig_size = *comp_size = len;
        }


	else
	{
	    int32 rec_len=0;


	    rec_len = HPread_drec(file_id, data_id, &local_ptbuf);
	    if (rec_len <= 0)
		HGOTO_ERROR(DFE_INTERNAL, FAIL);


	    p = local_ptbuf;
	    INT16DECODE(p, sp_tag);


	    if (sp_tag == SPECIAL_COMP)
	    {

		p = p + 2;
		INT32DECODE(p, len);
		*orig_size = len;


		if (len == 0)
		{
		    *comp_size = len;
		}

		else
		{

		    UINT16DECODE(p, comp_ref);
		    if ((len = Hlength(file_id, DFTAG_COMPRESSED, comp_ref)) == FAIL)
			HGOTO_ERROR(DFE_BADLEN, FAIL);
		    *comp_size = len;
		}
	    }


	    else if (sp_tag == SPECIAL_CHUNKED)
	    {
	     if (HMCgetdatasize(file_id, p, comp_size, orig_size)==FAIL)
		  HGOTO_ERROR(DFE_INTERNAL, FAIL);
	    }


	    else if (sp_tag == SPECIAL_LINKED)
	    {
		INT32DECODE(p, len);
		*orig_size = *comp_size = len;
	    }
	}


	if (HTPendaccess(data_id) == FAIL)
	    HGOTO_ERROR(DFE_CANTENDACCESS, FAIL);
    }

    else
        HGOTO_ERROR(DFE_CANTACCESS, FAIL);

done:
    if(ret_value == FAIL)
    {
    }


    if (local_ptbuf != NULL)
	HDfree(local_ptbuf);

    return ret_value;
}
