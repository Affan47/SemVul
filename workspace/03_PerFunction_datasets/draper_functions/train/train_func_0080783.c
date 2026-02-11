_fiid_obj_field_end (fiid_obj_t obj, const char *field)
{
  unsigned int start = 0;
  unsigned int end = 0;

  assert (obj);
  assert (obj->magic == FIID_OBJ_MAGIC);
  assert (field);

  if (_fiid_obj_field_start_end (obj, field, &start, &end) < 0)
    return (-1);

  return (end);
}
