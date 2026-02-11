import_ver1(vpwentry* vpw, const str* data)
{
  const char* ptr;
  const char* end;


  if (data->s[data->len-1] != 0) return 0;

  ptr = data->s;
  end = ptr++ + data->len;

  if ((ptr = import_base(vpw, ptr, end)) == 0) return 0;
  if ((ptr = import_values(vpw, ptr, end)) == 0) return 0;


  vpw->is_mailbox_enabled = 1;

  return ptr == end;
}
