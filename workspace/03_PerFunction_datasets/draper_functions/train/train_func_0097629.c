LoadLVars( Obj lvars )
{
  UInt len,i;
  Obj *ptr;
  ADDR_OBJ(lvars)[0] = LoadSubObj();
  ((UInt *)ADDR_OBJ(lvars))[1] = LoadUInt();
  ADDR_OBJ(lvars)[2] = LoadSubObj();
  len = (SIZE_OBJ(lvars) - (2*sizeof(Obj)+sizeof(UInt)))/sizeof(Obj);
  ptr = ADDR_OBJ(lvars)+3;
  for (i = 0; i < len; i++)
    *ptr++ = LoadSubObj();
  return;
}
