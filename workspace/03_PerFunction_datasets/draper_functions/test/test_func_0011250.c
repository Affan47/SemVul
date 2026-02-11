PosString (
    Obj                 list,
    Obj                 val,
    Obj                 start )
{
    Int                 lenList;
    Int                 i;
    UInt1               valc;
    UInt1               *p;
    UInt                istart;


    if (!IS_INTOBJ(start))
      return Fail;

    istart = INT_INTOBJ(start);


    lenList = GET_LEN_STRING( list );


    if (TNUM_OBJ(val) != T_CHAR) return Fail;


    valc = *(UInt1*)ADDR_OBJ(val);


    p = CHARS_STRING(list);
    for ( i = istart; i < lenList && p[i] != valc; i++ );


    return (lenList <= i ? Fail : INTOBJ_INT(i+1));
}
