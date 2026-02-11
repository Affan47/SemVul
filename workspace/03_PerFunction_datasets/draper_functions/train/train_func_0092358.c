set_param_tiny(Item_param *param, uchar **pos, ulong len)
{
#ifndef EMBEDDED_LIBRARY
  if (len < 1)
    return;
#endif
  int8 value= (int8) **pos;
  param->set_int(param->unsigned_flag ? (longlong) ((uint8) value) :
                                        (longlong) value, 4);
  *pos+= 1;
}
