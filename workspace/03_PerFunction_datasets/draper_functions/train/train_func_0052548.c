dimension(uint32 *res_dim, const char **end) const
{
  uint32 n_objects;
  const char *data= m_data;
  Geometry_buffer buffer;
  Geometry *geom;

  if (no_data(data, 4))
    return 1;
  n_objects= uint4korr(data);
  data+= 4;

  *res_dim= 0;
  while (n_objects--)
  {
    uint32 wkb_type, length, dim;
    const char *end_data;

    if (no_data(data, WKB_HEADER_SIZE))
      return 1;
    wkb_type= uint4korr(data + 1);
    data+= WKB_HEADER_SIZE;
    if (!(geom= create_by_typeid(&buffer, wkb_type)))
      return 1;
    geom->set_data_ptr(data, (uint32) (m_data_end - data));
    if (geom->dimension(&dim, &end_data))
      return 1;
    set_if_bigger(*res_dim, dim);
    if (end_data)
      data= end_data;
    else if ((length= geom->get_data_size()) == GET_SIZE_ERROR)
      return 1;
    else
      data+= length;
  }
  *end= data;
  return 0;
}
