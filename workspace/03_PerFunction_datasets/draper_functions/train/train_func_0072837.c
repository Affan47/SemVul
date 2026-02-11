fiid_obj_packet_sufficient (fiid_obj_t obj)
{
  int ret;

  if (!obj || obj->magic != FIID_OBJ_MAGIC)
    return (-1);

  if (!obj->makes_packet_sufficient)
    return _fiid_obj_packet_valid (obj, 0);

  if (!(ret = _fiid_obj_packet_valid (obj, 0)))
    {
      fiid_err_t save_errnum = obj->errnum;

      if (_fiid_obj_packet_valid (obj, 1) == 1)
        return (1);

      obj->errnum = save_errnum;
    }
  return (ret);
}
