val_str_ascii(String *str)
{
  DBUG_ASSERT(fixed == 1);
  String * sptr= args[0]->val_str(str);
  str->set_charset(&my_charset_bin);
  if (sptr)
  {
    uchar digest[16];

    null_value=0;
    MY_MD5_HASH(digest,(uchar *) sptr->ptr(), sptr->length());
    if (str->alloc(32))
    {
      null_value=1;
      return 0;
    }
    array_to_hex((char *) str->ptr(), digest, 16);
    str->length((uint) 32);
    return str;
  }
  null_value=1;
  return 0;
}
