_dxfFloatField(Object f, int *floatflag)
{
  Array a;
  Type type;
  int i;
  Object sub;

  *floatflag = 1;

  switch (DXGetObjectClass(f)) {
    case (CLASS_FIELD):
     if (DXEmptyField((Field)f)) return OK;

     if (!(a = (Array)(DXGetComponentValue((Field)f, "data")))) {
       return OK;
     }
     if (!(DXGetArrayInfo((Array)a, NULL, &type, NULL, NULL, NULL))) {
       DXSetError(ERROR_BAD_PARAMETER,"bad data component");
       return ERROR;
     }
     if (type != TYPE_FLOAT) {
       *floatflag = 0;
     }
     break;
    case (CLASS_GROUP):


     i = 0;
     while ((sub=(Object)DXGetPart((Object)f, i))) {
       i++;
       if (!(a = (Array)(DXGetComponentValue((Field)sub, "data")))) {
         continue;
       }
       if (!(DXGetArrayInfo((Array)a, NULL, &type, NULL, NULL, NULL))) {
         DXSetError(ERROR_BAD_PARAMETER,"bad data component");
         return ERROR;
       }
       if (type != TYPE_FLOAT) {
         *floatflag = 0;
         goto done;
       }
     }
     break;
     default:
     break;
   }
done:
   return OK;
}
