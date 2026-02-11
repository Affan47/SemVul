HXIstaccess(accrec_t * access_rec, int16 acc_mode)
{
    CONSTR(FUNC, "HXIstaccess");
    extinfo_t  *info = NULL;
    filerec_t  *file_rec = NULL;
    int32       data_off;
    uint8       local_ptbuf[12];
    int32       ret_value = SUCCEED;


    file_rec = HAatom_object(access_rec->file_id);
    if (BADFREC(file_rec) || !(file_rec->access & acc_mode))
        HGOTO_ERROR(DFE_ARGS, FAIL);


    access_rec->special = SPECIAL_EXT;
    access_rec->posn = 0;
    access_rec->access = (uint32)(acc_mode|DFACC_READ);


    if(HTPinquire(access_rec->ddid,NULL,NULL,&data_off,NULL)==FAIL)
        HGOTO_ERROR(DFE_INTERNAL, FAIL);


    access_rec->special_info = HIgetspinfo(access_rec);
    if (access_rec->special_info)
      {
          info = (extinfo_t *) access_rec->special_info;
          info->attached++;
      }
    else
      {
          if (HPseek(file_rec, data_off + 2) == FAIL)
              HGOTO_ERROR(DFE_SEEKERROR, FAIL);
          if (HP_read(file_rec, local_ptbuf, 12) == FAIL)
              HGOTO_ERROR(DFE_READERROR, FAIL);

          access_rec->special_info = HDmalloc((uint32) sizeof(extinfo_t));
          info = (extinfo_t *) access_rec->special_info;
          if (info==NULL)
            HGOTO_ERROR(DFE_NOSPACE, FAIL);

          {
              uint8      *p = local_ptbuf;
              INT32DECODE(p, info->length);
              INT32DECODE(p, info->extern_offset);
              INT32DECODE(p, info->length_file_name);
          }
          info->extern_file_name = (char *) HDmalloc((uint32) info->length_file_name + 1);
          if (!info->extern_file_name)
              HGOTO_ERROR(DFE_NOSPACE, FAIL);
          if (HP_read(file_rec, info->extern_file_name, info->length_file_name) == FAIL)
              HGOTO_ERROR(DFE_READERROR, FAIL);

          info->extern_file_name[info->length_file_name] = '\0';


          info->file_open = FALSE;
          info->attached = 1;
      }

    file_rec->attach++;
    ret_value = HAregister_atom(AIDGROUP,access_rec);

done:
  if(ret_value == FAIL)
    {
        if(access_rec!=NULL)
            HIrelease_accrec_node(access_rec);
        if(info !=NULL)
          {
              if (info->extern_file_name != NULL)
                  HDfree(info->extern_file_name);
              HDfree(info);
          }
    }


  return ret_value;
}
