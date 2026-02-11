do_save_field_metadata(uchar *metadata_ptr)
{
  DBUG_ASSERT(field_length <= 65535);
  int2store((char*)metadata_ptr, field_length);
  return 2;
}
