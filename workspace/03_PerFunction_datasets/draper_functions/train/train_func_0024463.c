Htell(int32 access_id)
{
  CONSTR(FUNC, "Htell");
  accrec_t   *access_rec;
  int32     ret_value = SUCCEED;


  HEclear();

  access_rec = HAatom_object(access_id);
  if (access_rec == (accrec_t *) NULL)
    HGOTO_ERROR(DFE_ARGS, FAIL);


  ret_value = (int32)access_rec->posn;

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}
