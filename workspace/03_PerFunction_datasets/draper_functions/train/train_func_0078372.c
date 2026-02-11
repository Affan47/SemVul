Hwrite(int32 access_id, int32 length, const void * data)
{
  CONSTR(FUNC, "Hwrite");
  filerec_t  *file_rec;
  accrec_t   *access_rec;
  int32       data_len;
  int32       data_off;
  int32       ret_value = SUCCEED;


  HEclear();
  access_rec = HAatom_object(access_id);
  if (access_rec == (accrec_t *) NULL
      || !(access_rec->access & DFACC_WRITE)
      || data == NULL)
    HGOTO_ERROR(DFE_ARGS, FAIL);


  if (access_rec->special)
    {
      ret_value = (*access_rec->special_func->write) (access_rec, length, data);
      goto done;
    }


  file_rec = HAatom_object(access_rec->file_id);
  if (BADFREC(file_rec))
    HGOTO_ERROR(DFE_INTERNAL, FAIL);


  if (access_rec->new_elem == TRUE)
    {
      Hsetlength(access_id, length);
      access_rec->appendable = TRUE;
    }


  if(HTPinquire(access_rec->ddid,NULL,NULL,&data_off,&data_len)==FAIL)
      HGOTO_ERROR(DFE_INTERNAL, FAIL);


  if (length <= 0
      || (!access_rec->appendable && length + access_rec->posn > data_len))
    HGOTO_ERROR(DFE_BADSEEK, FAIL);


  if (access_rec->appendable && length + access_rec->posn > data_len)
    {


      if (data_len + data_off != file_rec->f_end_off)
        {

          if (HLconvert(access_id, access_rec->block_size, access_rec->num_blocks) == FAIL)
            {
              access_rec->appendable = FALSE;
              HGOTO_ERROR(DFE_BADSEEK, FAIL);
            }


          if ((ret_value = Hwrite(access_id, length, data)) == FAIL)
            HGOTO_ERROR(DFE_WRITEERROR, FAIL);
          goto done;
        }


      if(HTPupdate(access_rec->ddid,-2,access_rec->posn+length)==FAIL)
          HGOTO_ERROR(DFE_INTERNAL, FAIL);
    }


  if (HPseek(file_rec, access_rec->posn + data_off) == FAIL)
    HGOTO_ERROR(DFE_SEEKERROR, FAIL);

  if (HP_write(file_rec, data, length) == FAIL)
    HGOTO_ERROR(DFE_WRITEERROR, FAIL);


  if (file_rec->f_cur_off > file_rec->f_end_off)
    file_rec->f_end_off = file_rec->f_cur_off;


  access_rec->posn += length;

  ret_value = length;

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}
