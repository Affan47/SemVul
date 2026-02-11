m_PickInvalidate(Object *in, Object *out)
{
  Object o = NULL, leaf=NULL;
  Field pickfield;
  int poke, pick, depth, exclude;


  if (!in[0]) {
    DXSetError(ERROR_BAD_PARAMETER, "missing input");
    goto error;
  }
  o = (Object)DXCopy(in[0], COPY_STRUCTURE);
  if (!o)
    goto error;


  if (!(DXGetObjectClass(in[1])==CLASS_FIELD)) {
    DXSetError(ERROR_DATA_INVALID,"pickfield must be a field");
    goto error;
  }


  if (!in[1] || DXEmptyField((Field)in[1])) {
    out[0] = o;
    return OK;
  }
  pickfield = (Field)in[1];


  if (in[2]) {
    if (!DXExtractInteger((Object)in[2], &exclude)) {
      DXSetError(ERROR_BAD_PARAMETER,"exclude must be either 0 or 1");
      goto error;
    }
    if ((exclude !=0) &&(exclude != 1)) {
      DXSetError(ERROR_BAD_PARAMETER,"exclude must be either 0 or 1");
      goto error;
    }
  }
  else {
    exclude = 0;
  }


  if (exclude==0) {
    if (!SetValidity(o, 0))
      goto error;
  }
  else {
    if (!SetValidity(o, 1))
      goto error;
  }


  if (!in[3]) {
    poke = -1;
  }
  else {
    if (!DXExtractInteger(in[3], &poke)) {
      DXSetError(ERROR_BAD_PARAMETER,"poke must be a non-negative integer");
      goto error;
    }
    if (poke < 0) {
      DXSetError(ERROR_BAD_PARAMETER,"poke must be a non-negative integer");
      goto error;
    }
  }


  if (!in[4]) {
    pick = -1;
  }
  else {
    if (!DXExtractInteger(in[4], &pick)) {
      DXSetError(ERROR_BAD_PARAMETER,"depth must be a non-negative integer");
      goto error;
    }
    if (pick < 0) {
      DXSetError(ERROR_BAD_PARAMETER,"depth must be a non-negative integer");
      goto error;
    }
  }


  if (!in[5]) {
    depth = -1;
  }
  else {
    if (!DXExtractInteger(in[5], &depth)) {
      DXSetError(ERROR_BAD_PARAMETER,"depth must be a non-negative integer");
      goto error;
    }
    if (depth < 0) {
      DXSetError(ERROR_BAD_PARAMETER,"depth must be a non-negative integer");
      goto error;
    }
  }


  if (!DoPick(o, pickfield, exclude, poke, pick, depth, &leaf))
    goto error;


  out[0] = o;
  out[1] = leaf;
  return OK;


 error:
  DXDelete(o);
  return ERROR;
}
