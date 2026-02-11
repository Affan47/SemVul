stringsfromobj(LObject *obj, char * *x)
{
  if (obj->type != LSTRING  && obj->type != LSTRINGS) return 0;
  *x = LSTRINGVAL(obj);
  return 1;
}
