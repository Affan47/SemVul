Hsetlength(int32 aid, int32 length)
{
  CONSTR(FUNC, "Hsetlength");
  accrec_t   *access_rec;
  filerec_t  *file_rec;
  int32       offset;
  intn       ret_value = SUCCEED;


  HEclear();

  if ((access_rec = HAatom_object(aid)) == NULL)
    HGOTO_ERROR(DFE_ARGS, FAIL);


  if (access_rec->new_elem != TRUE)
    HGOTO_ERROR(DFE_ARGS, FAIL);

  file_rec = HAatom_object(access_rec->file_id);
  if (BADFREC(file_rec))
    HGOTO_ERROR(DFE_ARGS, FAIL);


  if ((offset = HPgetdiskblock(file_rec, length, FALSE)) == FAIL)
      HGOTO_ERROR(DFE_SEEKERROR, FAIL);


  if(HTPupdate(access_rec->ddid,offset,length)==FAIL)
      HGOTO_ERROR(DFE_INTERNAL, FAIL);


  access_rec->new_elem = FALSE;

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}
