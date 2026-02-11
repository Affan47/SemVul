set_param_str(Item_param *param, uchar **pos, ulong len)
{
  ulong length= get_param_length(pos, len);
  if (length > len)
    length= len;
  param->set_str((const char *)*pos, length);
  *pos+= length;
}
