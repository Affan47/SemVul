HashMultifield(
  struct multifield *theSegment,
  unsigned theRange)
  {
   unsigned long length, i;
   unsigned int tvalue;
   unsigned int count;
   struct field *fieldPtr;
   union
     {
      double fv;
      unsigned int liv;
     } fis;


   count = 0;
   length = theSegment->multifieldLength;
   fieldPtr = theSegment->theFields;


   for (i = 0;
        i < length;
        i++)
     {
      switch(fieldPtr[i].type)
         {
          case MULTIFIELD:
            count += HashMultifield((struct multifield *) fieldPtr[i].value,theRange);
            break;

          case FLOAT:
            fis.fv = ValueToDouble(fieldPtr[i].value);
            count += (fis.liv * (i + 29))  +
                     (int) ValueToDouble(fieldPtr[i].value);
            break;

          case INTEGER:
            count += (((int) ValueToLong(fieldPtr[i].value)) * (i + 29)) +
                             ValueToLong(fieldPtr[i].value);
            break;

          case FACT_ADDRESS:
          case EXTERNAL_ADDRESS:
#if OBJECT_SYSTEM
          case INSTANCE_ADDRESS:
#endif
            count += (unsigned int) (((int) fieldPtr[i].value) * (i + 29));
            break;

          case SYMBOL:
          case STRING:
#if OBJECT_SYSTEM
          case INSTANCE_NAME:
#endif
            tvalue = (unsigned) HashSymbol(ValueToString(fieldPtr[i].value),theRange);
            count += (unsigned) (tvalue * (i + 29));
            break;
         }
     }


   return(count);
  }
