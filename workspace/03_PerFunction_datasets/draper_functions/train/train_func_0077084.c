fiid_obj_clear (fiid_obj_t obj)
{
  unsigned int i;

  if (!obj || obj->magic != FIID_OBJ_MAGIC)
    return (-1);

  secure_memset (obj->data, '\0', obj->data_len);
  for (i =0; i < obj->field_data_len; i++)
    obj->field_data[i].set_field_len = 0;

  obj->errnum = FIID_ERR_SUCCESS;
  return (0);
}
