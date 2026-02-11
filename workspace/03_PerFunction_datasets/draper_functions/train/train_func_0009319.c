ProdListList (
    Obj                 listL,
    Obj                 listR )
{
    Obj                 listP;
    Obj                 elmP;
    Obj                 elmL;
    Obj                 elmR;
    Int                 lenL,lenR,len;
    Int                 i;
    Int                 imm;


    lenL = LEN_LIST( listL );
    lenR = LEN_LIST( listR );
    len =  (lenL < lenR) ? lenL : lenR;

    listP = 0;
    imm = 0;
    for (i = 1; i <= len; i++)
      {
        elmL = ELM0_LIST( listL, i );
        elmR = ELM0_LIST( listR, i );
        if (elmL && elmR)
          {
            elmP = PROD( elmL, elmR );
            if (listP)
              listP = SUM( listP, elmP );
            else
              {
                listP = elmP;
                imm = !IS_MUTABLE_OBJ(listP);
              }
          }
    }

    if (imm && IS_MUTABLE_OBJ(listP))
      MakeImmutable(listP);

    if (!listP)
      ErrorMayQuit("Inner product multiplication of lists: no summands", 0, 0);


    return listP;
}
