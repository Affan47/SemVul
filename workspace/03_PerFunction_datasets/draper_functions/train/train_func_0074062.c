val_int()
{
  DBUG_ASSERT(fixed == 1);
  uint byte_result = 0;
  ulonglong result = 0;
  const char *p,* end;
  char c = '.';
  char buff[36];
  int dot_count= 0;

  String *s, tmp(buff, sizeof(buff), &my_charset_latin1);
  if (!(s = args[0]->val_str_ascii(&tmp)))
    goto err;
  null_value=0;

  end= (p = s->ptr()) + s->length();
  while (p < end)
  {
    c = *p++;
    int digit = (int) (c - '0');
    if (digit >= 0 && digit <= 9)
    {
      if ((byte_result = byte_result * 10 + digit) > 255)
	goto err;
    }
    else if (c == '.')
    {
      dot_count++;
      result= (result << 8) + (ulonglong) byte_result;
      byte_result = 0;
    }
    else
      goto err;
  }
  if (c != '.')
  {


    switch (dot_count) {
    case 1: result<<= 8;
    case 2: result<<= 8;
    }
    return (result << 8) + (ulonglong) byte_result;
  }

err:
  null_value=1;
  return 0;
}
