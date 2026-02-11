fiid_obj_get_all (fiid_obj_t obj,
                  void *data,
                  unsigned int data_len)
{
  unsigned int bytes_len;
  int bits_len;

  if (!obj || obj->magic != FIID_OBJ_MAGIC)
    return (-1);

  if (!data)
    {
      obj->errnum = FIID_ERR_PARAMETERS;
      return (-1);
    }

  if ((bits_len = fiid_obj_len (obj)) < 0)
    return (-1);

  if (bits_len == (obj->data_len * 8))
    bytes_len = obj->data_len;
  else
    bytes_len = BITS_ROUND_BYTES (bits_len);

  if (data_len < bytes_len)
    {
      obj->errnum = FIID_ERR_OVERFLOW;
      return (-1);
    }

  memset (data, '\0', data_len);

  if (bytes_len == obj->data_len)
    memcpy (data, obj->data, bytes_len);
  else
    {
      unsigned int bytes_written = 0, max_bits_counter = 0, set_bits_counter = 0,
        optional_bits_counter = 0, data_index = 0, obj_data_index = 0;
      unsigned int i;


      for (i = 0; i < obj->field_data_len; i++)
        {
          unsigned int max_field_len = obj->field_data[i].max_field_len;
          unsigned int set_field_len = obj->field_data[i].set_field_len;

          max_bits_counter += max_field_len;

          if (set_field_len)
            {
              if (optional_bits_counter)
                {
                  obj->errnum = FIID_ERR_DATA_NOT_BYTE_ALIGNED;
                  goto cleanup;
                }

              if (set_field_len != max_field_len)
                {


                  if ((set_bits_counter + set_field_len) % 8)
                    {
                      obj->errnum = FIID_ERR_DATA_NOT_BYTE_ALIGNED;
                      goto cleanup;
                    }
                }

              set_bits_counter += set_field_len;
              if (!(set_bits_counter % 8))
                {
                  unsigned int max_bytes_count = BITS_ROUND_BYTES (max_bits_counter);
                  unsigned int set_bytes_count = BITS_ROUND_BYTES (set_bits_counter);

                  memcpy (data + data_index,
                          obj->data + obj_data_index,
                          set_bytes_count);

                  bytes_written += set_bytes_count;
                  data_index += set_bytes_count;
                  obj_data_index += max_bytes_count;
                  set_bits_counter = 0;
                  max_bits_counter = 0;
                }
            }
          else
            {


              if (set_bits_counter)
                {
                  obj->errnum = FIID_ERR_DATA_NOT_BYTE_ALIGNED;
                  goto cleanup;
                }


              optional_bits_counter += max_field_len;
              if (optional_bits_counter && !(optional_bits_counter % 8))
                {

                  if (optional_bits_counter != max_bits_counter)
                    {
                      obj->errnum = FIID_ERR_DATA_NOT_BYTE_ALIGNED;
                      goto cleanup;
                    }

                  obj_data_index += BITS_ROUND_BYTES (optional_bits_counter);
                  optional_bits_counter = 0;
                  max_bits_counter = 0;
                }
            }
        }


      if (set_bits_counter)
        {
          obj->errnum = FIID_ERR_DATA_NOT_BYTE_ALIGNED;
          goto cleanup;
        }

      if (bytes_written != bytes_len)
        {
          obj->errnum = FIID_ERR_DATA_NOT_BYTE_ALIGNED;
          goto cleanup;
        }
    }

  obj->errnum = FIID_ERR_SUCCESS;
  return (bytes_len);

 cleanup:
  if (data)
    memset (data, '\0', data_len);
  return (-1);
}
