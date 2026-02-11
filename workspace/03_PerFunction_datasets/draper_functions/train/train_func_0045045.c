Hoffset(int32 file_id, uint16 tag, uint16 ref)
{
  CONSTR(FUNC, "Hoffset");
  int32       access_id;
  int32       offset=FAIL;
  int32       ret_value = SUCCEED;


  HEclear();


  access_id = Hstartread(file_id, tag, ref);
  if (access_id == FAIL)
    HGOTO_ERROR(DFE_ARGS, FAIL);

  if ((ret_value = HQueryoffset(access_id, &offset)) == FAIL)
    HERROR(DFE_INTERNAL);

  if(Hendaccess(access_id)==FAIL)
      HGOTO_ERROR(DFE_CANTENDACCESS, FAIL);

  ret_value = offset;

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}
