val_str(String *str)
{
  DBUG_ASSERT(fixed == 1);
  char buff[MAX_FIELD_WIDTH], *ptr, *end;
  String tmp(buff, sizeof(buff), system_charset_info);
  String *res, *remove_str;

  res= args[0]->val_str(str);
  if ((null_value=args[0]->null_value))
    return 0;
  remove_str= &remove;
  if (arg_count == 2)
  {
    remove_str= args[1]->val_str(&tmp);
    if ((null_value= args[1]->null_value))
      return 0;
  }

  const uint remove_length= remove_str->length();
  if (remove_length == 0 ||
      remove_length > res->length())
    return res;

  ptr= (char*) res->ptr();
  end= ptr+res->length();
  const char * const r_ptr= remove_str->ptr();
#ifdef USE_MB
  if (use_mb(res->charset()))
  {
    ptr= trim_left_mb(res, ptr, end, remove_str);

    char *p=ptr;
    register uint32 l;
 loop:
    while (ptr + remove_length < end)
    {
      if ((l= my_ismbchar(res->charset(), ptr,end)))
        ptr+= l;
      else
        ++ptr;
    }
    if (ptr + remove_length == end && !memcmp(ptr,r_ptr,remove_length))
    {
      end-=remove_length;
      ptr=p;
      goto loop;
    }
    ptr=p;
  }
  else
#endif
  {
    while (ptr+remove_length <= end && !memcmp(ptr,r_ptr,remove_length))
      ptr+=remove_length;
    while (ptr + remove_length <= end &&
	   !memcmp(end-remove_length,r_ptr,remove_length))
      end-=remove_length;
  }
  if (ptr == res->ptr() && end == ptr+res->length())
    return res;
  tmp_value.set(*res,(uint) (ptr - res->ptr()),(uint) (end-ptr));
  return &tmp_value;
}
