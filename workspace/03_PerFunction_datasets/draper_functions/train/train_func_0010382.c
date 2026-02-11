jp2_find_handler (
                        int p_id
                        )
{
  unsigned int i, l_handler_size = sizeof(jp2_header) / sizeof(opj_jp2_header_handler_t);
  for
    (i=0;i<l_handler_size;++i)
  {
    if
      (jp2_header[i].id == p_id)
    {
      return &jp2_header[i];
    }
  }
  return 00;
}
