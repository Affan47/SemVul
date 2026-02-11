SetValidity(Object o, int validity)
{
  Object subo;
  int i;
  InvalidComponentHandle handle=NULL;


  switch (DXGetObjectClass(o)) {


  case (CLASS_GROUP):


    for (i=0; (subo = DXGetEnumeratedMember((Group)o, i, NULL)); i++)
      if (!SetValidity(subo, validity))
         goto error;
    break;


  case (CLASS_XFORM):


    DXGetXformInfo((Xform)o, &subo, NULL);
    if (!SetValidity(subo, validity))
       goto error;
    break;


  case (CLASS_CLIPPED):


    DXGetClippedInfo((Clipped)o, &subo, NULL);
    if (!SetValidity(subo, validity))
       goto error;
    break;


  case (CLASS_FIELD):


    if (DXEmptyField((Field)o))
      return OK;


    if (DXGetComponentValue((Field)o, "connections")) {
      handle = DXCreateInvalidComponentHandle(o, NULL, "connections");
      if (!handle)
         goto error;
      if (validity==0) {
        if (!DXSetAllInvalid(handle))
          goto error;
      }
      else {
        if (!DXSetAllValid(handle))
          goto error;
      }
    }
    else {
      handle = DXCreateInvalidComponentHandle(o, NULL, "positions");
      if (!handle)
         goto error;
      if (validity==0) {
        if (!DXSetAllInvalid(handle))
          goto error;
      }
      else {
        if (!DXSetAllValid(handle))
          goto error;
      }
    }
    if (!DXSaveInvalidComponent((Field)o, handle))
       goto error;

    break;
    default:
      break;
  }


  DXFreeInvalidComponentHandle(handle);
  return OK;
 error:
  DXFreeInvalidComponentHandle(handle);
  return ERROR;
}
