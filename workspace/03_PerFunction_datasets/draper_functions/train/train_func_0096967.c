VSinquire(int32 vkey,
          int32 *nelt,
          int32 *interlace,
          char *fields,
          int32 *eltsize,
          char *vsname      )
{
  intn ret_value = SUCCEED;
  intn status;
  CONSTR(FUNC, "VSinquire");


    if (HAatom_group(vkey) != VSIDGROUP)
        HGOTO_ERROR(DFE_ARGS, FAIL);


    if (fields)
      {
        status = VSgetfields(vkey, fields);
        ret_value = (status == FAIL)? FAIL: ret_value;
      }
    if (nelt)
      {
        *nelt = VSelts(vkey);
        ret_value = (*nelt == FAIL)? FAIL: ret_value;
      }
    if (interlace)
      {
        *interlace = VSgetinterlace(vkey);
        ret_value = (*interlace == FAIL)? FAIL: ret_value;
      }
    if (eltsize)
      {
        *eltsize = VSsizeof(vkey, fields);
        ret_value = (*eltsize == FAIL)? FAIL: ret_value;
      }
    if (vsname)
      {
        status = VSgetname(vkey, vsname);
        ret_value = (status == FAIL)? FAIL: ret_value;
      }

done:
  if(ret_value == FAIL)
    {

    }


    return ret_value;

}
