DFSDsetrange(VOIDP maxi, VOIDP mini)
{
    int32       numtype;
    uint32      localNTsize;
    intn        i;
    uint8      *p1, *p2;
    intn        ret_value = SUCCEED;
    CONSTR(FUNC, "DFSDsetrange");

    HEclear();


    if (library_terminate == FALSE)
        if(DFSDIstart()==FAIL)
            HGOTO_ERROR(DFE_CANTINIT, FAIL);

    p1 = &(Writesdg.max_min[0]);
    for (i = 0; i < 16; i++)
        *p1++ = 0;


    if (Writesdg.numbertype == DFNT_NONE)
        DFSDsetNT(DFNT_FLOAT32);

    numtype = Writesdg.numbertype;
    localNTsize = (uint32)DFKNTsize((numtype | DFNT_NATIVE) & (~DFNT_LITEND));
    p1 = (uint8 *) maxi;
    p2 = (uint8 *) mini;

    HDmemcpy((uint8 *) &(Writesdg.max_min[0]), p1, localNTsize);
    HDmemcpy((uint8 *) &(Writesdg.max_min[localNTsize]), p2, localNTsize);

    Ref.maxmin = 0;

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}
