val_str(String *str)
{
  DBUG_ASSERT(fixed == 1);
  Geometry_buffer buffer;
  String arg_val;
  String *wkt= args[0]->val_str_ascii(&arg_val);

  if ((null_value= args[0]->null_value))
    return 0;

  Gis_read_stream trs(wkt->charset(), wkt->ptr(), wkt->length());
  uint32 srid= 0;

  if ((arg_count == 2) && !args[1]->null_value)
    srid= (uint32)args[1]->val_int();

  str->set_charset(&my_charset_bin);
  if (str->reserve(SRID_SIZE, 512))
    return 0;
  str->length(0);
  str->q_append(srid);
  if ((null_value= !Geometry::create_from_wkt(&buffer, &trs, str, 0)))
    return 0;
  return str;
}
