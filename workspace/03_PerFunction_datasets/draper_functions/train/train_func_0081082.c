FuncZERO_GF2VEC_2 (
    Obj                 self,
    Obj                 len )
{
    Obj                 zero;


    if (!IS_INTOBJ(len))
      ErrorMayQuit("ZERO_GF2VEC2: length must be a small integer, not a %s",
		(Int)TNAM_OBJ(len),0L);

    NEW_GF2VEC( zero, TYPE_LIST_GF2VEC, INT_INTOBJ(len) );
    SET_LEN_GF2VEC( zero, INT_INTOBJ(len) );
    return zero;
}
