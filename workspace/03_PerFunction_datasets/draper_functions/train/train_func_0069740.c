FuncADD_GF2VEC_GF2VEC_SHIFTED( Obj self, Obj vec1, Obj vec2, Obj len2, Obj off)
{
  Int off1, len2a;
  if (!IS_INTOBJ(off))
    ErrorMayQuit("ADD_GF2VEC_GF2VEC_SHIFTED: offset should be a small integer not a %s",
	      (Int)TNAM_OBJ(off), 0L);
  off1 = INT_INTOBJ(off);
  if (off1 < 0)
    {
       ErrorMayQuit("ADD_GF2VEC_GF2VEC_SHIFTED: <offset> must be a non-negative integer",
			   0,0);
    }
  len2a = INT_INTOBJ(len2);
  while (len2a < 0 && len2a <= LEN_GF2VEC(vec2))
    {
      len2 = ErrorReturnObj("ADD_GF2VEC_GF2VEC_SHIFTED: <len2> must be a non-negative integer\nand less than the actual length of the vector",
			   0,0,"you can replace <len2> via 'return <len2>;'");
      len2a = INT_INTOBJ(len2);
    }
  if (len2a + off1 > LEN_GF2VEC(vec1))
    ResizeGF2Vec(vec1, len2a+ off1);
  AddShiftedVecGF2VecGF2( vec1, vec2, len2a, off1);
  return (Obj) 0;
}
