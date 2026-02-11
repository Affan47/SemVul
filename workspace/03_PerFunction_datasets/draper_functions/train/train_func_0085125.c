FuncCHAR_SINT (
    Obj             self,
    Obj             val )
{
  Int             chr;


agains:
  while ( ! IS_INTOBJ(val) ) {
      val = ErrorReturnObj(
	  "<val> must be an integer (not a %s)",
	  (Int)TNAM_OBJ(val), 0L,
	  "you can replace <val> via 'return <val>;'" );
  }
  chr = INT_INTOBJ(val);
  if ( 127 < chr || chr < -128 ) {
      val = ErrorReturnObj(
	  "<val> must be an integer between -128 and 127",
	  0L, 0L, "you can replace <val> via 'return <val>;'" );
      goto agains;
  }


    return ObjsChar[CHAR_SINT(chr)];
}
