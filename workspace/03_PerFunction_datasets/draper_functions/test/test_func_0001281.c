DFSDsetfillvalue(VOIDP fill_value)
{
  int32       numtype;
  uint32      localNTsize;
  intn        ret_value = SUCCEED;
  CONSTR(FUNC, "DFSDsetfillvalue");


  HEclear();


    if (library_terminate == FALSE)
        if(DFSDIstart()==FAIL)
            HGOTO_ERROR(DFE_CANTINIT, FAIL);


  if (Ref.fill_value == -1 && Writesdg.fill_fixed == TRUE)
    {
      HGOTO_ERROR(DFE_INTERNAL, FAIL);
    }
  else
    {

      numtype = Writesdg.numbertype;
      localNTsize = (uint32)DFKNTsize((numtype | DFNT_NATIVE) & (~DFNT_LITEND));


      Ref.fill_value = 0;
      if (HDmemcpy(Writesdg.fill_value, fill_value, localNTsize) != NULL)
        ret_value = SUCCEED;
      else
        ret_value = FAIL;
    }

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}
