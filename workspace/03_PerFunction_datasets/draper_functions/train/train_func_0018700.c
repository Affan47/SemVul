releaseValue(Value *value)
{
   value->~Value();

   if (value->asLValue())
      mem_LValue.release(value);
   else
   if (value->asImm())
      mem_ImmediateValue.release(value);
   else
   if (value->asSym())
      mem_Symbol.release(value);
}


}
