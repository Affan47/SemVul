FuncSHALLOW_SIZE (
    Obj                 self,
    Obj                 obj )
{
  if (IS_INTOBJ(obj) || IS_FFE(obj))
    return INTOBJ_INT(0);
  else
    return ObjInt_UInt( SIZE_BAG( obj ) );
}
